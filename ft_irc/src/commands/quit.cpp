/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/13 16:27:22 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"

void quit(Client *client, std::vector<std::string> const &args)
{
	std::string reason = args.empty() ? "Leaving..." : args[0];

	if (reason.at(0) == ':')
		reason = reason.substr(1);

	// TODO: disconnect when we have access to server
	// server->disconnectClient(client->getFd())
	client->reply(RPL_QUIT(client->getPrefix(), reason));
}
