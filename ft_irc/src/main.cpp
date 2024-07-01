/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:18:58 by herbie            #+#    #+#             */
/*   Updated: 2024/07/01 14:06:59 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include <iostream>
#include <csignal>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}

	try
	{
		Server::stop = false;

		Server server(argv[1], argv[2]);

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
