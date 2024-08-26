/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 10:29:57 by herbie           ###   ########.fr       */
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

	// std::cout << message;
}

void Client::write(const std::string &msg) const
{
	if (send(_fd, msg.c_str(), msg.size(), 0) < 0)
		throw std::runtime_error("Failed to send message to client");
}

void Client::joinChannel(Channel *channel)
{
	// TODO implement this in channel.cpp instead

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

	write(":" + getPrefix() + " JOIN " + _channel->getName() + "\r\n");
	write(":ft_irc.server MODE " + _channel->getName() + " +nt\r\n");
	write(":ft_irc.server 353 " + getNickname() + " = " + _channel->getName() + " :" + users + "\r\n");
	write(":ft_irc.server 366 " + getNickname() + " " + _channel->getName() + " :End of /NAMES list.\r\n");

	_channel->broadcast(":ft_irc.server JOIN " + _channel->getName() + "\r\n");
}

std::string Client::getPrefix() const
{
	std::string username = _username.empty() ? "" : "!" + _username;
	std::string hostname = _hostname.empty() ? "" : "@" + _hostname;

	return _nickname + username + hostname;
}
