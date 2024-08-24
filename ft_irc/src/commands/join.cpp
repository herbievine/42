/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 14:02:50 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
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
	if (args.empty() || args.size() < 2)
	{
		client->sendRaw(":ft_irc.server 461 " + client->getNickname() + " TOPIC :Not enough parameters\r\n");
		return;
	}

	std::vector<std::string> channels = split(args[0], ',');
	std::vector<std::string> keys = split(args[1], ',');

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string name = channels[i];
		std::string password = keys.size() > i ? keys[i] : "";

		Channel *channel = client->getChannel();

		if (channel)
		{
			client->sendRaw(":ft_irc.server 405 " + client->getNickname() + " " + name + " :You have joined too many channels\r\n");
			return;
		}
		else if (name[0] != '#' && name[0] != '&')
		{
			client->sendRaw(":ft_irc.server 403 " + client->getNickname() + " " + name + " :No such channel\r\n");
			return;
		}

		channel = server->getChannel(name);

		if (!channel)
		{
			channel = server->createChannel(name, password);
			channel->addOperator(client);

			client->joinChannel(channel);

			return;
		}

		if (channel->getLimit() > 0 && channel->getClients().size() >= channel->getLimit())
		{
			client->sendRaw(":ft_irc.server 471 " + client->getNickname() + " " + name + " :Cannot join channel (+l)\r\n");
			return;
		}
		else if (!password.empty() && channel->getK() != password)
		{
			client->sendRaw(":ft_irc.server 475 " + client->getNickname() + " " + name + " :Cannot join channel (+k)\r\n");
			return;
		}
		else if (channel->isInviteOnly())
		{
			client->sendRaw(":ft_irc.server 473 " + client->getNickname() + " " + name + " :Cannot join channel (+i)\r\n");
			return;
		}

		client->joinChannel(channel);
	}
}
