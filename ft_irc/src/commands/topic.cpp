/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 19:06:49 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The TOPIC command is used to change or view the topic of the given
 * channel. If <topic> is not given, either RPL_TOPIC or RPL_NOTOPIC is returned
 * specifying the current channel topic or lack of one. If <topic> is an empty
 * string, the topic for the channel will be cleared.

 * If the client sending this command is not joined to the given channel, and
 * tries to view its’ topic, the server MAY return the ERR_NOTONCHANNEL (442)
 * numeric and have the command fail.

 * If RPL_TOPIC is returned to the client sending this command,
 * RPL_TOPICWHOTIME SHOULD also be sent to that client.

 * If the protected topic mode is set on a channel, then clients MUST have
 * appropriate channel permissions to modify the topic of that channel. If a
 * client does not have appropriate channel permissions and tries to change the
 * topic, the ERR_CHANOPRIVSNEEDED (482) numeric is returned and the command
 * will fail.

 * If the topic of a channel is changed or cleared, every client in that channel
 * (including the author of the topic change) will receive a TOPIC command with
 * the new topic as argument (or an empty argument if the topic was cleared)
 * alerting them to how the topic has changed. If the <topic> param is provided
 * but the same as the previous topic (ie. it is unchanged), servers MAY notify
 * the author and/or other users anyway.
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#topic-message
 */
void topic(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " TOPIC :Not enough parameters\r\n");
		return;
	}

	Channel *channel = server->getChannel(args[0]);

	if (!channel)
	{
		client->write(":ft_irc.server 403 " + client->getNickname() + " " + args[0] + " :No such channel\r\n");
		return;
	}
	else if (!channel->isClientInChannel(client))
	{
		client->write(":ft_irc.server 442 " + client->getNickname() + " " + channel->getName() + " :You're not on that channel\r\n");
		return;
	}

	if (args.size() == 1)
	{
		if (channel->getTopic().empty())
		{
			client->write(":ft_irc.server 331 " + client->getNickname() + " " + channel->getName() + " :No topic is set\r\n");
		}
		else
		{
			client->write(":ft_irc.server 332 " + client->getNickname() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
		}

		return;
	}

	if (channel->getTopicPrivilege() && !channel->isOperator(client))
	{
		client->write(":ft_irc.server 482 " + client->getNickname() + " " + channel->getName() + " :You're not channel operator\r\n");
		return;
	}

	std::string newTopic = args[1];

	for (size_t i = 2; i < args.size(); ++i)
		newTopic += " " + args[i];

	channel->setTopic(newTopic);

	channel->broadcast(":" + client->getPrefix() + " TOPIC " + channel->getName() + " :" + newTopic + "\r\n");
}
