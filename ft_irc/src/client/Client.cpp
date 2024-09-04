/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/09/03 15:21:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <fstream>

Client::Client(int fd, std::string &ip, std::string &hostname) : _fd(fd), _ip(ip), _hostname(hostname), _state(UNAUTHENTICATED), _channelCount(0)
{
}

Client::Client(const Client &src) : _fd(src._fd), _ip(src._ip), _hostname(src._hostname), _state(src._state), _nickname(src._nickname), _username(src._username), _realname(src._realname), _channelCount(src._channelCount)
{
}

Client::~Client()
{
}

Client &Client::operator=(const Client &rhs)
{
	if (this != &rhs)
	{
		_fd = rhs._fd;
		_ip = rhs._ip;
		_hostname = rhs._hostname;

		_state = rhs._state;

		_nickname = rhs._nickname;
		_username = rhs._username;
		_realname = rhs._realname;

		_channelCount = rhs._channelCount;
	}

	return *this;
}

void Client::write(const std::string &msg) const
{
	if (send(_fd, msg.c_str(), msg.size(), 0) < 0)
		throw std::runtime_error("Failed to send message to client");
}

std::string Client::getPrefix() const
{
	std::string username = _username.empty() ? "" : "!" + _username;
	std::string hostname = _hostname.empty() ? "" : "@" + _hostname;

	return _nickname + username + hostname;
}
