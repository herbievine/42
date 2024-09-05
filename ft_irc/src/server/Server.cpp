/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/09/05 13:04:18 by jcros            ###   ########.fr       */
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
#include <unordered_map>

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

	std::unordered_map<std::string, Channel *>::iterator chan_it = _channels.begin();

	while (chan_it != _channels.end())
	{
		delete chan_it->second;
		++chan_it;
	}

	std::map<int, Client *>::iterator client_it = _clients.begin();

	while (client_it != _clients.end())
	{
		delete client_it->second;
		close(client_it->first);
		++client_it;
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
	else if (fcntl(_lsd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Could not set socket options");

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
		if (poll(_fds.data(), _fds.size(), -1) < 0 && Server::stop == false)
			throw std::runtime_error("Poll failed");

		for (size_t i = 0; i < _fds.size(); i++)
		{
			int polled_fd = _fds[i].fd;

			if (_fds[i].revents & POLLHUP)
				disconnectClient(polled_fd, "");
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

	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Could not set socket options");

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

				struct command_handler
				{
					std::string label;
					void (*handler)(Server *, Client *, const std::vector<std::string> &);
					int auth;
				};

				struct command_handler handlers[] = {
						{"CAP", &cap, UNAUTHENTICATED},
						{"INVITE", &invite, REGISTERED},
						{"JOIN", &join, REGISTERED},
						{"KICK", &kick, REGISTERED},
						{"MODE", &mode, REGISTERED},
						{"NICK", &nick, AUTHENTICATED},
						{"PART", &part, REGISTERED},
						{"PASS", &pass, UNAUTHENTICATED},
						{"PING", &ping, UNAUTHENTICATED},
						{"PONG", &pong, UNAUTHENTICATED},
						{"PRIVMSG", &privmsg, REGISTERED},
						{"QUIT", &quit, UNAUTHENTICATED},
						{"TOPIC", &topic, REGISTERED},
						{"USER", &user, AUTHENTICATED},
						{"WHO", &who, REGISTERED},
				};

				for (size_t i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++)
				{
					if (std::string(line).rfind(handlers[i].label, 0) == 0)
					{
						if (line.size() == handlers[i].label.size())
							line += " ";

						std::vector<std::string> args = split(std::string(line).substr(handlers[i].label.size() + 1));

						if (handlers[i].auth == UNAUTHENTICATED)
							handlers[i].handler(this, client, args);
						else if (handlers[i].auth == AUTHENTICATED && client->getState() != UNAUTHENTICATED)
							handlers[i].handler(this, client, args);
						else if (handlers[i].auth == REGISTERED && client->getState() == REGISTERED)
							handlers[i].handler(this, client, args);

						else
						{
							client->write(":ft_irc.server 451 * :You have not registered\r\n");
						}
					}
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

void Server::disconnectClient(int fd, const std::string reason)
{
	Client *client = _clients.at(fd);

	std::unordered_map<std::string, Channel *>::iterator it = _channels.begin();

	while (it != _channels.end())
	{
		it->second->broadcast(":" + client->getPrefix() + " QUIT :" + reason + "\r\n", client);
		
		it->second->removeClient(client);

		if (it->second->getClients().size() == 0)
			_channels.erase(it++);
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

void Server::registerChannel(Channel *channel)
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

void Server::deleteChannel(Channel *channel)
{
	_channels.erase(channel->getName());
}

void Server::handleSignal(int signal)
{
	(void)signal;
	stop = true;
}
