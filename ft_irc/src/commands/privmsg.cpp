/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:05:01 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 19:05:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

void privmsg(Server *server, Client *client, std::vector<std::string> const &args)
{
	std::string target;
	std::string message;

	if (args.size() < 2)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
		return;
	}

	target = args[0];
	std::vector<std::string>::const_iterator it = args.begin();
	for (size_t i = 1; i < args.size(); ++i)
	{
		message.append(args[i] + " ");
	}

	if (!message.empty())
	{
		message.pop_back();
	}

	Channel *channel = server->getChannel(target);

	if (channel)
	{
		if (!channel->isClientInChannel(client))
		{
			client->write(ERR_CANNOTSENDTOCHAN(client->getNickname(), target) + "\r\n");
			return;
		}
		std::vector<Client *> clients = channel->getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if (*it != client)
			{
				(*it)->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
			}
		}
	}
	else
	{
		if (!client->getChannel())
		{
			client->write(ERR_NOSUCHNICK(client->getNickname(), target) + "\r\n");
			return;
		}
		channel = client->getChannel();
		Client *ClientTarget = channel->getClientByNickname(target);
		if (!ClientTarget)
		{
			client->write(ERR_NOSUCHNICK(client->getNickname(), target) + "\r\n");
		}
		else
		{
			ClientTarget->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
		}
	}
}
