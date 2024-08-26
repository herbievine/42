/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:29:19 by juliencros        #+#    #+#             */
/*   Updated: 2024/08/26 14:51:07 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// incite = if someone try to connect to a channel in invite only mode will be rejected
// only if the user is invited by the channel operator

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
#include <vector>

void invite(Server *server, const Client *client, std::vector<std::string> const &args)
{
	if (args.size() < 2)
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " INVITE :Not enough parameters\r\n");
	}

	std::string nickname = args[0];
	std::string target = args[1];

	Channel *channel = server->getChannel(target);
	if (!channel)
	{
		client->write(":ft_irc.server 403 " + client->getNickname() + " " + target + " :No such channel\r\n");
		return;
	}

	Client *targetClient = server->getClientByNickname(nickname);
	if (!targetClient)
	{
		client->write(":ft_irc.server 401 " + client->getNickname() + " " + nickname + " :No such nick/channel\r\n");
		return;
	}

	if (!channel->isOperator(client))
	{
		client->write(":ft_irc.server 482 " + client->getNickname() + " " + target + " :You're not channel operator\r\n");
		return;
	}

	if (channel->isClientInChannel(targetClient))
	{
		client->write(":ft_irc.server 443 " + client->getNickname() + " " + nickname + " " + target + " :is already on channel\r\n");
		return;
	}

	channel->setInvited(targetClient);
	client->write(":ft_irc.server 341 " + client->getPrefix() + " " + nickname + " " + target + "\r\n");
}
