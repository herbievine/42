/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/19 12:38:35 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

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
	else if (!password.empty() && channel->getKey() != password)
	{
		client->reply(ERR_BADCHANNELKEY(client->getNickname(), channelName));
		return;
	}

	client->joinChannel(channel);
}
