/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 12:42:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <vector>

void pass(Client *client, std::vector<std::string> const &args)
{
	if (args.size() != 1)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PASS"));
		return;
	}

	if (client->getNickname().length() > 0)
	{
		client->reply(ERR_ALREADYREGISTERED(client->getNickname()));
		return;
	}

	if (args[0] != "password")
	{
		client->reply(ERR_PASSWDMISMATCH(client->getNickname()));
		return;
	}

	client->authenticate();
}
