/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/23 17:51:36 by juliencros       ###   ########.fr       */
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
 * For each channel in the parameter of this command, if the channel exists and
 * the client is not joined to it, they will receive an ERR_NOTONCHANNEL (442)
 * reply and that channel will be ignored. If the channel does not exist, the
 * client will receive an ERR_NOSUCHCHANNEL (403) reply and that channel will be
 * ignored.
 *
 * This message may be sent from a server to a client to notify the client that
 * someone has been removed from a channel. In this case, the message <source>
 * will be the client who is being removed, and <channel> will be the channel
 * which that client has been removed from. Servers SHOULD NOT send multiple
 * channels in this message to clients, and SHOULD distribute these
 * multiple-channel PART messages as a series of messages with a single channel
 * name on each. If a PART message is distributed in this way, <reason> (if it
 * exists) should be on each of these messages.
 *
 * @param server
 * @param client
 * @param args
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
