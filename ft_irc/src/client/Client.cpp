/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/13 15:48:06 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "iostream"
#include <sys/socket.h>
#include <fstream>

Client::Client()
{
	_fd = -1;
	_ip = "";
	_hostname = "";
	_nickname = "";
	_username = "";
	_realname = "";
}

Client::Client(int fd, std::string ip, std::string hostname)
{
	_fd = fd;
	_ip = ip;
	_hostname = hostname;
	_nickname = "";
	_username = "";
	_realname = "";
}

Client::Client(const Client &src)
{
}

Client::~Client()
{
}

Client &Client::operator=(const Client &rhs)
{
	if (this != &rhs)
	{
		this->_fd = rhs._fd;
		this->_ip = rhs._ip;
	}

	return *this;
}

void Client::reply(const std::string &msg) const
{
	std::string message = ":" + getPrefix() + " " + msg + "\r\n";

	std::cout << message << std::endl;

	if (send(_fd, message.c_str(), message.size(), 0) < 0)
		throw std::runtime_error("Failed to send message to client");
	// TODO: this is debug
	else
		std::cout << "[SENT] " << message;
}

std::string Client::getPrefix() const
{
	std::string username = _username.empty() ? "" : "!" + _username;
	std::string hostname = _hostname.empty() ? "" : "@" + _hostname;

	return _nickname + username + hostname;
}
