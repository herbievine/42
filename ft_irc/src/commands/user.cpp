/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 11:12:20 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The USER command is used at the beginning of a connection to specify
 * the username and realname of a new user.

 * It must be noted that <realname> must be the last parameter because it may
 * contain SPACE (' ', 0x20) characters, and should be prefixed with a colon (:)
 * if required.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#user-message
 */
void user(Server *server, Client *client, std::vector<std::string> const &args)
{
    (void)server;

	if (client->getState() == REGISTERED)
	{
		client->write(":ft_irc.server 462 " + client->getNickname() + " :You may not reregister\r\n");
		return;
	}
	else if (args.empty() || args.size() < 4)
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " USER :Not enough parameters\r\n");
		return;
	}

	std::string realname = args[3];

	for (size_t i = 2; i < args.size(); ++i)
		realname += " " + args[i];

	if (realname[0] == ':')
		realname = realname.erase(0, 1);

	client->setUsername(args[0]);
	client->setRealname(realname);
	client->setState(REGISTERED);

	client->write(":" + client->getPrefix() + " 001 " + client->getNickname() + " :Welcome " + client->getNickname() + " to the ft_irc network\r\n");
}
