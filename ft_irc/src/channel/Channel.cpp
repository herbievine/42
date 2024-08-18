/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 17:18:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
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

Channel::Channel(std::string &name, std::string &password, Client *admin) : _limit(0)
{
	_name = name;
	_key = password;
	_admin = admin;
}

Channel::Channel(const Channel &src)
{
}

Channel::~Channel()
{
}

Channel &Channel::operator=(const Channel &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_admin = rhs._admin;
	}

	return *this;
}

void Channel::broadcast(std::string message)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		(*it)->reply(message);
		it++;
	}
}

std::vector<std::string> Channel::getNicknames() const
{
	std::vector<std::string> nicknames;

	std::vector<Client *>::const_iterator it = _clients.begin();

	while (it != _clients.end())
	{
		nicknames.push_back((*it)->isChannelOperator() ? "@" : "" + (*it)->getNickname());
		it++;
	}

	return nicknames;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
}
