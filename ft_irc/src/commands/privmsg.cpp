/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:05:01 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 15:44:02 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

void privmsg(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
	{
		client->reply(":ft_irc.server 406 " + client->getNickname() + " PRIVMSG :Not enough parameters\r\n");
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
			client->write(":ft_irc.server 404 " + client->getNickname() + " " + target + " :Cannot send to channel\r\n");
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
		client->write(":ft_irc.server 401 " + client->getNickname() + " PRIVMSG :No such nick/channel\r\n");
		return;
	}

	channel = client->getChannel();
	const Client *TargetClient = channel->getClientByNickname(target);

	if (!TargetClient)
	{
		client->write(":ft_irc.server 401 " + client->getNickname() + " PRIVMSG :No such nick/channel\r\n");
	}
	else
	{
		TargetClient->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
	}
}
