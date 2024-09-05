/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:02:20 by herbie            #+#    #+#             */
/*   Updated: 2024/09/05 13:01:56 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"

void kick(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args.size() < 2)
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " KICK :Not enough parameters\r\n");
		return;
	}

	std::string name = args[0];
	std::string nickname = args[1];
	std::string reason = "Kicked";

	if (args.size() >= 3)
	{
		reason = args[2];

		if (reason[0] == ':')
			reason.erase(0, 1);

		for (size_t i = 3; i < args.size(); ++i)
			reason += " " + args[i];
	}

	Channel *channel = server->getChannel(name);

	if (!channel)
	{
		client->write(":ft_irc.server 403 " + client->getNickname() + " " + name + " :No such channel\r\n");
		return;
	}
	else if (!channel->isOperator(client))
	{
		client->write(":ft_irc.server 482 " + client->getNickname() + " " + name + " :You're not channel operator\r\n");
		return;
	}

	Client *target = channel->getClientByNickname(nickname);

	if (!target)
	{
		client->write(":ft_irc.server 401 " + client->getNickname() + " " + nickname + " :No such nick/channel\r\n");
		return;
	}

	channel->broadcast(":" + client->getPrefix() + " KICK " + name + " " + target->getNickname() + " :" + reason + "\r\n");
	channel->removeClient(target);
	
	if (channel->getClients().size() == 0)
	{
		server->deleteChannel(channel);
	}
}
