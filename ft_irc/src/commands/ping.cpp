/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/13 16:27:35 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"

void ping(Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PING"));
		return;
	}

	client->reply(RPL_PING(client->getPrefix(), args.at(0)));
}
