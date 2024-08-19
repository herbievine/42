/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/19 10:06:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

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
