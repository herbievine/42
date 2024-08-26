/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 16:23:01 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
#include <vector>

/**
 * @brief This command is used to query a list of users who match the provided
 * mask. The server will answer this command with zero, one or more
 * RPL_WHOREPLY, and end the list with RPL_ENDOFWHO.
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#who-message
 */
void who(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " WHO :Not enough parameters\r\n");
		return;
	}

	if (args[0][0] == '#')
	{
		Channel *channel = server->getChannel(args[0]);

		if (!channel)
		{
			client->write(":ft_irc.server 403 " + client->getNickname() + " " + args[0] + " :No such channel\r\n");
			return;
		}

		std::vector<Client *> clients = channel->getClients();
		std::vector<Client *>::iterator it = clients.begin();

		while (it != clients.end())
		{
			client->write(":ft_irc.server 352 " + client->getNickname() + " " + args[0] + " ~" + (*it)->getUsername() + " " + (*it)->getHostname() + " ft_irc.server " + (*it)->getNickname() + (channel->isOperator(*it) ? " *H :0 " : " H :0 ") + (*it)->getRealname() + "\r\n");
			it++;
		}

		client->write(":ft_irc.server 315 " + client->getNickname() + " " + args[0] + " :End of WHO list.\r\n");
	}
}
