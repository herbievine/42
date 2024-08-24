/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 13:27:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /**
//  * @brief The PART command removes the client from the given channel(s). On
//  * sending a successful PART command, the user will receive a PART message from
//  * the server for each channel they have been removed from. <reason> is the
//  * reason that the client has left the channel(s).
//  *
//  * For each channel in the parameter of this command, if the channel exists and
//  * the client is not joined to it, they will receive an ERR_NOTONCHANNEL (442)
//  * reply and that channel will be ignored. If the channel does not exist, the
//  * client will receive an ERR_NOSUCHCHANNEL (403) reply and that channel will be
//  * ignored.
//  *
//  * This message may be sent from a server to a client to notify the client that
//  * someone has been removed from a channel. In this case, the message <source>
//  * will be the client who is being removed, and <channel> will be the channel
//  * which that client has been removed from. Servers SHOULD NOT send multiple
//  * channels in this message to clients, and SHOULD distribute these
//  * multiple-channel PART messages as a series of messages with a single channel
//  * name on each. If a PART message is distributed in this way, <reason> (if it
//  * exists) should be on each of these messages.
//  *
//  * @param server
//  * @param client
//  * @param args
//  */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The JOIN command indicates that the client wants to join the given
 * channel(s), each channel using the given key for it. The server receiving the
 * command checks whether or not the client can join the given channel, and
 * processes the request. Servers MUST process the parameters of this command as
 * lists on incoming commands from clients, with the first <key> being used for
 * the first <channel>, the second <key> being used for the second <channel>,
 * etc.
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#join-message
 */
void join(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
		return;
	}

	std::string channelName = args[0];
	std::string password = "";

	if (args.size() > 1)
		password = args[1];

	// Channel *channel = client->getChannel();

	// if (channel)
	// {
	// 	client->reply(ERR_TOOMANYCHANNELS(client->getNickname(), channelName));
	// 	return;
	// }

	Channel *channel = server->getChannel(channelName);

	if (!channel)
	{
		channel = server->createChannel(channelName, password);
		channel->addOperator(client);

		client->joinChannel(channel);

		return;
	}

	if (channel->getLimit() > 0 && channel->getClients().size() >= channel->getLimit())
	{
		client->reply(ERR_CHANNELISFULL(client->getNickname(), channelName));
		return;
	}
	else if (!password.empty() && channel->getK() != password)
	{
		client->reply(ERR_BADCHANNELKEY(client->getNickname(), channelName));
		return;
	}

	client->joinChannel(channel);
}
