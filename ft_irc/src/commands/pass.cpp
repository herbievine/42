/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 14:08:46 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The PASS command is used to set a ‘connection password’. If set, the
 * password must be set before any attempt to register the connection is made.
 * This requires that clients send a PASS command before sending the NICK / USER
 * combination.
 *
 * The password supplied must match the one defined in the server configuration.
 * It is possible to send multiple PASS commands before registering but only the
 * last one sent is used for verification and it may not be changed once the
 * client has been registered.
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#pass-message
 */
void pass(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->sendRaw(":ft_irc.server 461 " + client->getNickname() + " PASS :Not enough parameters\r\n");
		return;
	}
	else if (client->getNickname().length() > 0)
	{
		client->sendRaw(":ft_irc.server 462 " + client->getNickname() + " :You may not reregister\r\n");
		return;
	}
	else if (args[0] != server->getPassword())
	{
		client->sendRaw(":ft_irc.server 464 " + client->getNickname() + " :Password incorrect\r\n");
		return;
	}

	client->authenticate();
}
