/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 12:42:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

void ping(Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PING"));
		return;
	}

	client->reply(RPL_PING(client->getPrefix(), args.at(0)));
}
