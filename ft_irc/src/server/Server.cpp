/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/12 16:03:57 by herbie           ###   ########.fr       */
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

void Server::start()
{
	struct sockaddr_in addr = {
			.sin_family = AF_INET,
			.sin_port = htons(this->_port),
			.sin_addr.s_addr = INADDR_ANY};

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

	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Could not set socket options");

	char hostname[NI_MAXHOST];
	int res = getnameinfo((struct sockaddr *)&addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (res != 0)
		throw std::runtime_error("Error while getting a hostname on a new client!");

	std::cout << "New connection from " << inet_ntoa(addr.sin_addr) << " (" << fd << ")" << std::endl;

	struct pollfd pfd = {
			.fd = fd,
			.events = POLLIN,
			.revents = 0};

	Client *client = new Client(fd, inet_ntoa(addr.sin_addr), hostname);

	std::cout << "New connection from " << client->getFd() << " (" << fd << ")" << std::endl;

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
			std::cout << "[" << _clients[fd]->getFd() << "] " << buffer << std::endl;

			if (std::string(buffer).rfind("PASS", 0) == 0)
				pass(_clients[fd], split(std::string(buffer).substr(5)));
			else if (std::string(buffer).rfind("NICK", 0) == 0)
				nick(_clients[fd], split(std::string(buffer).substr(5)));
			else
				std::cout << "[WARN] Command unhandled: " << buffer << std::endl;
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
