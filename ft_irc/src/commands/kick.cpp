/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:02:20 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 15:47:35 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"

void kick(Server *server, const Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args.size() < 2)
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " KICK :Not enough parameters\r\n");
		return;
	}

	std::string name = args[0];
	std::string nickname = args[1];
	std::string reason = "";

	if (args[2][0] == ':')
		reason = args[2].substr(1);
	else
		reason = args[2];

	for (size_t i = 3; i < args.size(); ++i)
		reason += " " + args[i];

	if (reason.empty())
		reason = "Kicked";

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

	const Client *target = channel->getClientByNickname(nickname);

	if (!target)
	{
		client->write(":ft_irc.server 401 " + client->getNickname() + " " + nickname + " :No such nick/channel\r\n");
		return;
	}

	channel->broadcast(":" + client->getPrefix() + " KICK " + name + " " + target->getNickname() + " :" + reason + "\r\n");
	channel->removeClient(target);
}
