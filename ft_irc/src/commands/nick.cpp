/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/13 11:50:57 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"

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