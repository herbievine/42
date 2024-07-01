/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/07/01 15:27:30 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "iostream"
#include <sys/socket.h>
#include <fstream>

Client::Client(int fd, std::string ip) : _fd(fd), _ip(ip)
{
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

int Client::getFd() const
{
	return this->_fd;
}
