/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 14:01:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Server.hpp"
#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The NICK command is used to give the client a nickname or change the
 * previous one.
 *
 * If the server receives a NICK command from a client where the desired
 * nickname is already in use on the network, it should issue an ERR_NICKNAMEINUSE
 * numeric and ignore the NICK command.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#nick-message
 */
void nick(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args[0].empty())
	{
		client->sendRaw(":ft_irc.server 431 " + client->getNickname() + " :No nickname given\r\n");
		return;
	}

	for (size_t i = 0; i < args[0].length(); i++)
	{
		std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|";

		if (allowed.find(args[0][i]) == std::string::npos)
		{
			client->sendRaw(":ft_irc.server 432 " + client->getNickname() + " :Erroneous nickname\r\n");
			return;
		}
	}

	Client *other = server->getClientByNickname(args[0]);

	if (other)
	{
		client->sendRaw(":ft_irc.server 433 " + client->getNickname() + " " + args[0] + " :Nickname is already in use\r\n");
		return;
	}

	client->setNickname(args[0]);
}
