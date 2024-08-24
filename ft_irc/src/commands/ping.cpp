/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 14:10:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

/**
 * @brief The PING command is sent by either clients or servers to check the
 * other side of the connection is still connected and/or to check for
 * connection latency, at the application layer.
 *
 * The <token> may be any non-empty string.
 *
 * When receiving a PING message, clients or servers must reply to it with a
 * PONG message with the same <token> value. This allows either to match PONG
 * with the PING they reply to, for example to compute latency.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#ping-message
 */
void ping(Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->sendRaw(":ft_irc.server 461 " + client->getNickname() + " PING :Not enough parameters\r\n");
		return;
	}

	client->sendRaw(":ft_irc.server PONG ft_irc.server :" + args.at(0) + "\r\n");
}
