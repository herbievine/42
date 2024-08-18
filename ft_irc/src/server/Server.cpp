/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 21:00:10 by herbie           ###   ########.fr       */
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

Server::Server(std::string port, std::string password) : _lsd(-1) //: _password(password)
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

Server::Server(const Server &src)
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

void Server::createChannel(std::string name, std::string password, Client *admin)
{
	Channel *channel = new Channel(name, password, admin);

	_channels.push_back(channel);
}

Channel *Server::getChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i]->getName() == name)
			return _channels[i];
	}

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
	if (bind(_lsd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
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
			int fd = _fds[i].fd;

			if (_fds[i].revents & POLLHUP)
				disconnectClient(fd);
			else if (_fds[i].revents & POLLIN)
			{
				if (fd == _lsd)
					acceptConnection();
				else
					readFromClient(fd);
			}
		}
	}

	std::cout << "Gracefully shut server down" << std::endl;
}

void Server::acceptConnection()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	int fd = accept(_lsd, (struct sockaddr *)&addr, &len);
	if (fd < 0)
		throw std::runtime_error("Failed to accept connection");

	// if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
	// 	throw std::runtime_error("Could not set socket options");

	char hostname[NI_MAXHOST];
	int res = getnameinfo((struct sockaddr *)&addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (res != 0)
		throw std::runtime_error("Error while getting a hostname on a new client!");

	struct pollfd pfd = {
			.fd = fd,
			.events = POLLIN,
			.revents = 0};

	Client *client = new Client(fd, inet_ntoa(addr.sin_addr), hostname);

	std::cout << "New connection from " << client->getFd() << " (" << fd << ")" << std::endl;

	client->sendRaw(":ft_irc.server NOTICE * :***Welcome to ft_irc!\r\n");

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
			std::cout << "[NEW] " << buffer;

			if (std::string(buffer).rfind("CAP", 0) == 0)
				cap(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("JOIN", 0) == 0)
				join(this, _clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("NICK", 0) == 0)
				nick(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("PASS", 0) == 0)
				pass(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("PING", 0) == 0)
				ping(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("PONG", 0) == 0)
				pong(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("QUIT", 0) == 0)
				quit(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("USER", 0) == 0)
				user(_clients[fd], split(std::string(buffer).substr(5)));
			else
				std::cout << "[WARN] Command unhandled: " << buffer;
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

	std::cout << "[" << client->getNickname() << "]" << " disconnected" << std::endl;

	delete client;
}

void Server::handleSignal(int signal)
{
	(void)signal;
	stop = true;
}
