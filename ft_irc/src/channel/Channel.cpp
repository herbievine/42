/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/19 13:17:08 by herbie           ###   ########.fr       */
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

Channel::Channel(std::string &name, std::string &password) : _limit(0)
{
	_name = name;
	_key = password;
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
		nicknames.push_back((isOperator(*it) ? "@" : "") + (*it)->getNickname());

		it++;
	}

	return nicknames;
}

bool Channel::isOperator(Client *client) const
{
	std::map<std::string, bool>::const_iterator it = _operators.find(client->getNickname());

	if (it != _operators.end())
		return it->second;

	return false;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
}

void Channel::removeClient(Client *client)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (*it == client)
		{
			_clients.erase(it);
			break;
		}

		it++;
	}
}

void Channel::addOperator(Client *client)
{
	_operators[client->getNickname()] = true;
}

void Channel::removeOperator(Client *client)
{
	_operators[client->getNickname()] = false;
}
