/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 17:00:43 by herbie           ###   ########.fr       */
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

	_auth = false;

	_nickname = "";
	_username = "";
	_realname = "";
	_isRegistered = false;
	_hasBeenWelcomed = false;
}

Client::Client(int fd, std::string ip, std::string hostname)
{
	_fd = fd;
	_ip = ip;
	_hostname = hostname;

	_auth = false;

	_nickname = "";
	_username = "";
	_realname = "";
	_isRegistered = false;
	_hasBeenWelcomed = false;
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

void Client::joinChannel(Channel *channel)
{
	channel->addClient(this);
	_channel = channel;

	std::string users = "";
	std::vector<std::string> nicknames = _channel->getNicknames();
	std::vector<std::string>::iterator it = nicknames.begin();

	while (it != nicknames.end())
	{
		users.append(*it + " ");
		it++;
	}

	reply(RPL_NAMREPLY(_nickname, _channel->getName(), users));
	reply(RPL_ENDOFNAMES(_nickname, _channel->getName()));

	_channel->broadcast(RPL_JOIN(getPrefix(), _channel->getName()));
}

std::string Client::getPrefix() const
{
	std::string username = _username.empty() ? "" : "!" + _username;
	std::string hostname = _hostname.empty() ? "" : "@" + _hostname;

	return _nickname + username + hostname;
}
