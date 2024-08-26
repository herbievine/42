/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:05:01 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 13:46:56 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

void privmsg(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
		return;
	}

	std::string target = args[0];
	std::string message = "";

	if (args[1][0] == ':')
		message = args[1].substr(1);
	else
		message = args[1];

	for (size_t i = 2; i < args.size(); ++i)
		message += " " + args[i];

	Channel *channel = server->getChannel(target);

	if (channel)
	{
		if (!channel->isClientInChannel(client))
		{
			client->write(ERR_CANNOTSENDTOCHAN(client->getNickname(), target) + "\r\n");
			return;
		}

		std::vector<Client *> clients = channel->getClients();
		std::vector<Client *>::iterator it = clients.begin();

		while (it != clients.end())
		{
			if (*it != client)
				(*it)->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");

			++it;
		}

		return;
	}

	if (!client->getChannel())
	{
		client->write(ERR_NOSUCHNICK(client->getNickname(), target) + "\r\n");
		return;
	}

	channel = client->getChannel();
	const Client *TargetClient = channel->getClientByNickname(target);

	if (!TargetClient)
	{
		client->write(ERR_NOSUCHNICK(client->getNickname(), target) + "\r\n");
	}
	else
	{
		TargetClient->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
	}
}
