/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 13:28:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The PART command removes the client from the given channel(s). On
 * sending a successful PART command, the user will receive a PART message from
 * the server for each channel they have been removed from. <reason> is the
 * reason that the client has left the channel(s).
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#part-message
 */
void part(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
		return;
	}

	std::string channelName = args[0];

	Channel *channel = server->getChannel(channelName);

	if (!channel)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
		return;
	}

	std::vector<Client *> clients = channel->getClients();
	std::vector<Client *>::iterator it = std::find(clients.begin(), clients.end(), client);

	if (it == clients.end())
	{
		client->reply(ERR_NOTONCHANNEL(client->getNickname(), channelName));
		return;
	}

	channel->removeClient(client);
	channel->broadcast(":" + client->getNickname() + " PART " + channelName + " :" + (args.size() > 1 ? args[1] : ""));
}
