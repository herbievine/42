/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/09/04 14:10:30 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
#include <algorithm>
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
		client->write(":ft_irc.server 461 " + client->getNickname() + " PART :Not enough parameters\r\n");
		return;
	}

	std::vector<std::string> channels = split(args[0], ',');

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string name = channels[i];

		Channel *channel = server->getChannel(name);

		if (!channel)
		{
			client->write(":ft_irc.server 403 " + client->getNickname() + " " + name + " :No such channel\r\n");
			return;
		}

		std::vector<Client *> clients = channel->getClients();
		std::vector<Client *>::iterator it = std::find(clients.begin(), clients.end(), client);

		if (it == clients.end())
		{
			client->write(":ft_irc.server 442 " + client->getNickname() + " " + name + " :You're not on that channel\r\n");
			return;
		}

		client->write(":" + client->getNickname() + " PART " + name + " :" + (args.size() > 1 ? args[1] : "Leaving...") + "\r\n");

		channel->removeClient(client);
		channel->broadcast(":" + client->getNickname() + " PART " + name + " :" + (args.size() > 1 ? args[1] : "Leaving...") + "\r\n");

		if (channel->getClients().size() == 0)
		{
			server->deleteChannel(channel);
		}
	}
}
