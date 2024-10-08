/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:05:01 by herbie            #+#    #+#             */
/*   Updated: 2024/09/03 15:20:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

void privmsg(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
	{
		client->write(":ft_irc.server 406 " + client->getNickname() + " PRIVMSG :Not enough parameters\r\n");
		return;
	}

	std::string target = args[0];
	std::string message;

	if (args.size() >= 2)
	{
		message = args[1];

		if (message[0] == ':')
			message.erase(0, 1);

		for (size_t i = 2; i < args.size(); ++i)
			message += " " + args[i];
	}

	const Channel *channel = server->getChannel(target);

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

	const Client *TargetClient = server->getClientByNickname(target);

	if (!TargetClient)
	{
		client->write(":ft_irc.server 401 " + client->getNickname() + " PRIVMSG :No such nick/channel\r\n");
	}
	else
	{
		TargetClient->write(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
	}
}
