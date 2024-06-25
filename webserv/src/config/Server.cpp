/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 13:12:23 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "iostream"
#include <fstream>

Server::Server()
{
	_name = "_";
	_host = "0.0.0.0";
	_port = 80;
	_root = "/";
}

Server::Server(const Server &src)
{
}

Server::~Server()
{
}

Server &Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		this->_host = rhs._host;
		this->_port = rhs._port;
		this->_root = rhs._root;
		this->_indexes = rhs._indexes;
		this->_methods = rhs._methods;
	}

	return *this;
}

std::string Server::getName() const
{
	return this->_name;
}

std::string Server::getHost() const
{
	return this->_host;
}

int Server::getPort() const
{
	return this->_port;
}

std::string Server::getRoot() const
{
	return this->_root;
}

std::vector<std::string> Server::getIndexes() const
{
	return this->_indexes;
}

std::vector<std::string> Server::getMethods() const
{
	return this->_methods;
}

void Server::setName(std::string name)
{
	this->_name = name;
}

void Server::setHost(std::string host)
{
	this->_host = host;
}

void Server::setPort(int port)
{
	this->_port = port;
}

void Server::setRoot(std::string root)
{
	this->_root = root;
}

void Server::addIndex(std::string index)
{
	this->_indexes.push_back(index);
}

void Server::addMethod(std::string method)
{
	this->_methods.push_back(method);
}

std::ostream &operator<<(std::ostream &o, const Server &server)
{
	o << "Server Name: " << server.getName() << std::endl;
	o << "Host: " << server.getHost() << std::endl;
	o << "Port: " << server.getPort() << std::endl;
	o << "Root: " << server.getRoot() << std::endl;
	o << "Indexes: " << std::endl;

	std::vector<std::string> indexes = server.getIndexes();

	for (std::vector<std::string>::iterator it = indexes.begin(); it != indexes.end(); it++)
	{
		o << " - " << *it << std::endl;
	}

	o << "Methods: " << std::endl;

	std::vector<std::string> methods = server.getMethods();

	for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); it++)
	{
		o << " - " << *it << std::endl;
	}

	return o;
}
