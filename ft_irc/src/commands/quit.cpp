/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/09/05 10:25:12 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include <vector>

/**
 * @brief The QUIT command is used to terminate a client’s connection to the
 * server. The server acknowledges this by replying with an ERROR message and
 * closing the connection to the client.
 *
 * This message may also be sent from the server to a client to show that a
 * client has exited from the network. This is typically only dispatched to
 * clients that share a channel with the exiting user. When the QUIT message is
 * sent to clients, <source> represents the client that has exited the network.

 * When connections are terminated by a client-sent QUIT command, servers SHOULD
 * prepend <reason> with the ASCII string "Quit: " when sending QUIT messages to
 * other clients, to represent that this user terminated the connection
 * themselves. This applies even if <reason> is empty, in which case the reason
 * sent to other clients SHOULD be just this "Quit: " string. However, clients
 * SHOULD NOT change behaviour based on the prefix of QUIT message reasons, as
 * this is not required behaviour from servers.
 *
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#quit-message
 */
void quit(Server *server, Client *client, std::vector<std::string> const &args)
{
	(void)server;
	std::string reason = args.empty() ? "Leaving..." : args[0];

	if (reason.at(0) == ':')
		reason = reason.substr(1);

	server->disconnectClient(client->getFd(), reason);
	client->write(":ft_irc.server " + client->getNickname() + " QUIT :" + reason + "\r\n");
}
