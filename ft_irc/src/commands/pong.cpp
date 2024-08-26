/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 13:45:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The PONG command is used as a reply to PING commands, by both clients
 * and servers. The <token> should be the same as the one in the PING message
 * that triggered this PONG.

 * Servers MUST send a <server> parameter, and clients SHOULD ignore it. It
 * exists for historical reasons, and indicates the name of the server sending
 * the PONG. Clients MUST NOT send a <server> parameter.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#pong-message
 */
void pong(const Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " PONG :Not enough parameters\r\n");
		return;
	}

	client->write(":ft_irc.server PONG ft_irc.server :" + args.at(0) + "\r\n");
}
