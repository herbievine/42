/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:02:20 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:50:35 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"

void kick(Server *server, const Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args.size() < 2)
	{
		client->write(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK") + "\r\n");
		return;
	}

	std::string name = args[0];
	std::string nickname = args[1];
	std::string reason = args.size() > 2 ? args[2] : nickname;

	Channel *channel = server->getChannel(name);

	if (!channel)
	{
		client->write(ERR_NOSUCHCHANNEL(client->getNickname(), name) + "\r\n");
		return;
	}
	else if (!channel->isOperator(client))
	{
		client->write(ERR_CHANOPRIVSNEEDED(client->getNickname(), name) + "\r\n");
		return;
	}

	const Client *target = channel->getClientByNickname(nickname);

	if (!target)
	{
		client->write(ERR_NOSUCHNICK(client->getNickname(), nickname) + "\r\n");
		return;
	}

	channel->broadcast(RPL_KICK(client->getPrefix(), name, target->getNickname(), reason + "\r\n"));
	channel->removeClient(target);
}
