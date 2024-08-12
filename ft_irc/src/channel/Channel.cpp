/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/08/12 16:03:06 by herbie           ###   ########.fr       */
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

Channel::Channel(std::string &name, std::string &password, Client *admin) : _l(0)
{
	_name = name;
	_k = password;
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

void Channel::addClient(Client *client)
{
	_clients.push_back(client);
}
