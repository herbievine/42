/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 12:42:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

void nick(Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args[0].empty())
	{
		client->reply(ERR_NONICKNAMEGIVEN(client->getNickname()));
		return;
	}

	client->setNickname(args[0]);
	client->reply(RPL_WELCOME(client->getNickname()));
}
