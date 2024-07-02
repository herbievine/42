/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/07/02 17:56:01 by herbie           ###   ########.fr       */
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

	std::cout << "[" << client->getFd() << "]" << " connected" << std::endl;

	client->setNickname(args[0]);
	client->reply(RPL_WELCOME(client->getNickname()));

	std::cout << "[" << client->getNickname() << "]" << " connected" << std::endl;
}
