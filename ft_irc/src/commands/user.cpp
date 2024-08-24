/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 13:34:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
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
void user(Client *client, std::vector<std::string> const &args)
{
	if (client->isRegistered())
	{
		client->reply(ERR_ALREADYREGISTERED(client->getNickname()));
		return;
	}

	if (args.size() < 4)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "USER"));
		return;
	}

	client->setUsername(args[0]);
	client->setRealname(args[3]);

	client->reply(RPL_WELCOME(client->getUsername()));
}
