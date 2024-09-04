/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:57:10 by juliencros       ###   ########.fr       */
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

Channel::Channel(std::string &name, std::string &password) : _name(name), _k(password), _limit(0), _isInviteOnly(false), _topicPrivilege(false)
{
}

Channel::Channel(const Channel &src) : _name(src._name), _k(src._k), _limit(src._limit), _isInviteOnly(src._isInviteOnly), _topicPrivilege(src._topicPrivilege), _topic(src._topic)
{
}

Channel::~Channel()
{
}

Channel &Channel::operator=(const Channel &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_k = rhs._k;
		_limit = rhs._limit;
		_isInviteOnly = rhs._isInviteOnly;
		_topicPrivilege = rhs._topicPrivilege;
		_topic = rhs._topic;
	}

	return *this;
}

void Channel::broadcast(const std::string &message)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		(*it)->write(message);
		++it;
	}
}

void Channel::broadcast(const std::string &message, const Client *exclude)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (*it != exclude)
			(*it)->write(message);

		++it;
	}
}

std::vector<std::string> Channel::getNicknames() const
{
	std::vector<std::string> nicknames;

	std::vector<Client *>::const_iterator it = _clients.begin();

	while (it != _clients.end())
	{
		nicknames.push_back((isOperator(*it) ? "@" : "") + (*it)->getNickname());

		++it;
	}

	return nicknames;
}

bool Channel::isOperator(const Client *client) const
{
	std::map<std::string, bool>::const_iterator it = _operators.find(client->getNickname());

	if (it != _operators.end())
		return it->second;

	return false;
}

bool Channel::isClientInChannel(const Client *client) const
{
	std::vector<Client *>::const_iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (*it == client)
			return true;

		++it;
	}

	return false;
}

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
	_operators[client->getNickname()] = false;
}

void Channel::removeClient(const Client *client)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if (*it == client)
		{
			_clients.erase(it);
			break;
		}

		++it;
	}

	it = _invited.begin();

	while (it != _invited.end())
	{
		if (*it == client)
		{
			_invited.erase(it);
			break;
		}

		++it;
	}

	_operators.erase(client->getNickname());
}

void Channel::addOperator(const Client *client)
{
	_operators[client->getNickname()] = true;
}

void Channel::removeOperator(const Client *client)
{
	_operators[client->getNickname()] = false;
}

Client *Channel::getClientByNickname(const std::string &nickname)
{
	std::vector<Client *>::iterator it = _clients.begin();

	while (it != _clients.end())
	{
		if ((*it)->getNickname() == nickname)
			return *it;

		++it;
	}

	return nullptr;
}

void Channel::setInvited(Client *client)
{
	std::vector<Client *>::iterator it = _invited.begin();

	while (it != _invited.end())
	{
		if (*it == client)
			return;

		++it;
	}

	_invited.push_back(client);
}

bool Channel::isInvited(const Client *client)
{
	std::vector<Client *>::iterator it = _invited.begin();

	while (it != _invited.end())
	{
		if (*it == client)
			return true;

		++it;
	}

	return false;
}
