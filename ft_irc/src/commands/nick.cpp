/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 13:30:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The NICK command is used to give the client a nickname or change the
 * previous one.
 *
 * If the server receives a NICK command from a client where the desired
 * nickname is already in use on the network, it should issue an ERR_NICKNAMEINUSE
 * numeric and ignore the NICK command.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#nick-message
 */
void nick(Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args[0].empty())
	{
		client->reply(ERR_NONICKNAMEGIVEN(client->getNickname()));
		return;
	}

	client->setNickname(args[0]);
}
