/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:01:44 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <sys/socket.h>
#include <fstream>
#include <poll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

bool Server::stop = false;

Server::Server(const std::string &port, std::string &password) : _lsd(-1), _password(password)
{
	try
	{
		_port = std::stoi(port);
	}
	catch (std::exception &e)
	{
		throw std::runtime_error("Invalid port");
	}
}

Server::Server(const Server &src) : _port(src._port), _lsd(src._lsd), _fds(src._fds)
{
}

Server::~Server()
{
	if (_lsd != -1)
	{
		close(_lsd);
		_lsd = -1;
	}
}

Server &Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		this->_port = rhs._port;
		this->_lsd = rhs._lsd;
		this->_fds = rhs._fds;
	}

	return *this;
}

Channel *Server::getChannel(std::string &name)
{
	std::unordered_map<std::string, Channel *>::iterator it = _channels.find(name);

	if (it != _channels.end())
		return it->second;

	return nullptr;
}

void Server::start()
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port);
	addr.sin_addr.s_addr = INADDR_ANY;

	// Create a socket
	_lsd = socket(AF_INET, SOCK_STREAM, 0);
	if (_lsd < 0)
		throw std::runtime_error("Could not create socket");

	// Set socket options
	const int enable = 1;
	if (setsockopt(_lsd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("Could not set socket options");
	// else if (fcntl(_lsd, F_SETFL, O_NONBLOCK) < 0)
	// 	throw std::runtime_error("Could not set socket options");

	// Bind the socket
	if (bind(_lsd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0)
		throw std::runtime_error("Failed to bind socket");

	// Listen for incoming connections
	if (listen(_lsd, 10) < 0)
		throw std::runtime_error("Failed to listen for incoming connections");

	struct pollfd fd = {
			.fd = _lsd,
			.events = POLLIN,
			.revents = 0};

	_fds.push_back(fd);

	std::cout << "Server started on port " << _port << std::endl;

	while (Server::stop == false)
	{
		if (poll(_fds.data(), _fds.size(), -1) < 0)
			throw std::runtime_error("Poll failed");

		for (size_t i = 0; i < _fds.size(); i++)
		{
			int polled_fd = _fds[i].fd;

			if (_fds[i].revents & POLLHUP)
				disconnectClient(polled_fd);
			else if (_fds[i].revents & POLLIN)
			{
				if (polled_fd == _lsd)
					acceptConnection();
				else
					readFromClient(polled_fd);
			}
		}
	}

	std::cout << "Gracefully shut server down" << std::endl;
}

void Server::acceptConnection()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	int fd = accept(_lsd, reinterpret_cast<struct sockaddr *>(&addr), &len);
	if (fd < 0)
		throw std::runtime_error("Failed to accept connection");

	std::string welcome = ":ft_irc.server NOTICE * :*** Looking up your hostname...\r\n";
	send(fd, welcome.c_str(), welcome.size(), 0);

	// if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	// 	throw std::runtime_error("Could not set socket options");

	char hostname[NI_MAXHOST];
	int res = getnameinfo(reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (res != 0)
	{
		std::string message = ":ft_irc.server NOTICE * :*** Could not get hostname\r\n";
		send(fd, message.c_str(), message.size(), 0);

		throw std::runtime_error("Error while getting a hostname on a new client!");
	}

	std::string message = ":ft_irc.server NOTICE * :*** Found your hostname\r\n";
	send(fd, message.c_str(), message.size(), 0);

	struct pollfd pfd = {
			.fd = fd,
			.events = POLLIN,
			.revents = 0};

	std::string inet_addr = inet_ntoa(addr.sin_addr);
	std::string hostname_str = hostname;

	Client *client = new Client(fd, inet_addr, hostname_str);

	_fds.push_back(pfd);
	_clients.insert(std::pair<int, Client *>(fd, client));
}

void Server::readFromClient(int fd)
{
	char buffer[1024];

	memset(buffer, 0, sizeof(buffer));

	ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);

	if (bytes > 0)
	{
		buffer[bytes] = '\0';

		try
		{
			std::vector<std::string> args = split(buffer, '\n');
			std::vector<std::string>::iterator it = args.begin();

			while (it != args.end())
			{
				std::string line = *it;
				Client *client = _clients[fd];

				if (client->getState() == UNAUTHENTICATED)
				{
					if (std::string(line).rfind("PASS", 0) == 0)
						pass(this, client, split(std::string(line).substr(5)));
					else
						client->write(":ft_irc.server 451 * :You have not registered\r\n");
				}
				else if (client->getState() == AUTHENTICATED)
				{
					if (std::string(line).rfind("NICK", 0) == 0)
						nick(this, client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("USER", 0) == 0)
						user(client, split(std::string(line).substr(5)));
					else
						client->write(":ft_irc.server 451 * :You have not registered\r\n");
				}
				else if (client->getState() == REGISTERED)
				{
					if (std::string(line).rfind("CAP", 0) == 0)
						cap(client, split(std::string(line).substr(4)));
					else if (std::string(line).rfind("JOIN", 0) == 0)
						join(this, client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("PART", 0) == 0)
						part(this, client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("PING", 0) == 0)
						ping(client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("PONG", 0) == 0)
						pong(client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("QUIT", 0) == 0)
						quit(client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("TOPIC", 0) == 0)
						topic(this, client, split(std::string(line).substr(6)));
					else if (std::string(line).rfind("WHO", 0) == 0)
						who(this, client, split(std::string(line).substr(4)));
					else if (std::string(line).rfind("MODE", 0) == 0)
						mode(this, client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("KICK", 0) == 0)
						kick(this, client, split(std::string(line).substr(5)));
					else if (std::string(line).rfind("PRIVMSG", 0) == 0)
						privmsg(this, client, split(std::string(line).substr(8)));
				}
				else
				{
					client->write(":ft_irc.server 451 * :You have not registered\r\n");
				}

				++it;
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}

void Server::disconnectClient(int fd)
{
	Client *client = _clients.at(fd);

	std::unordered_map<std::string, Channel *>::iterator it = _channels.begin();

	while (it != _channels.end())
	{
		it->second->removeClient(client);

		if (it->second->getClients().empty())
		{
			delete it->second;
			_channels.erase(it++);
		}
		else
		{
			++it;
		}
	}

	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}

	_clients.erase(fd);
	close(fd);

	std::cout << "[" << client->getFd() << "]" << " disconnected" << std::endl;

	delete client;
}

void Server::registerNewChannel(Channel *channel)
{
	_channels[channel->getName()] = channel;
}

Client *Server::getClientByNickname(const std::string &nickname)
{
	std::map<int, Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (it->second->getNickname() == nickname)
			return it->second;

		++it;
	}

	return nullptr;
}

void Server::handleSignal(int signal)
{
	(void)signal;
	stop = true;
}
