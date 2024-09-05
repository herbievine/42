/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:18:58 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 12:11:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include <iostream>
#include <csignal>
#include <vector>
#include <string>

int main(int argc, const char *argv[])
{
	if (argc != 3)
	{
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}

	try
	{
		Server::stop = false;

		std::string port = argv[1];
		std::string password = argv[2];

		Server server(port, password);

		signal(SIGINT, Server::handleSignal);
		signal(SIGQUIT, Server::handleSignal);

		server.start();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}
