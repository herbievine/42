/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 10:18:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
#include <vector>

void who(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "WHO"));
		return;
	}

	DetectType type = detect(args[0]);

	if (type == DetectType::Channel)
	{
		Channel *channel = server->getChannel(args[0]);

		if (!channel)
		{
			client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), args[0]));
			return;
		}

		std::vector<Client *> clients = channel->getClients();
		std::vector<Client *>::iterator it = clients.begin();

		while (it != clients.end())
		{
			client->sendRaw(":ft_irc.server 352 " + client->getNickname() + " " + args[0] + " ~" + (*it)->getUsername() + " " + (*it)->getHostname() + " ft_irc.server " + (*it)->getNickname() + (channel->isOperator(*it) ? " *H :0 " : " H :0 ") + (*it)->getRealname() + "\r\n");
			it++;
		}

		client->sendRaw(":ft_irc.server 315 " + client->getNickname() + " " + args[0] + " :End of WHO list.\r\n");
	}
}
