/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:41:54 by herbie            #+#    #+#             */
/*   Updated: 2024/09/03 15:21:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../utils/utils.hpp"
#include <vector>

/**
 * @brief The JOIN command indicates that the client wants to join the given
 * channel(s), each channel using the given key for it. The server receiving the
 * command checks whether or not the client can join the given channel, and
 * processes the request. Servers MUST process the parameters of this command as
 * lists on incoming commands from clients, with the first <key> being used for
 * the first <channel>, the second <key> being used for the second <channel>,
 * etc.
 *
 * @param server
 * @param client
 * @param args
 *
 * @related https://modern.ircdocs.horse/#join-message
 */
void join(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty())
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " JOIN :Not enough parameters\r\n");
		return;
	}

	std::vector<std::string> channels = split(args[0], ',');
	std::vector<std::string> keys;

	if (args.size() == 2)
		keys = split(args[1], ',');

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string name = channels[i];
		std::string password = keys.size() > i ? keys[i] : "";

		// Channel *channel = client->getChannel();

		// if (channel)
		// {
		// 	client->write(":ft_irc.server 405 " + client->getNickname() + " " + name + " :You have joined too many channels\r\n");
		// 	return;
		// }
		// else 
		if (name[0] != '#' && name[0] != '&')
		{
			client->write(":ft_irc.server 403 " + client->getNickname() + " " + name + " :No such channel\r\n");
			return;
		}

		Channel *channel = server->getChannel(name);

		if (!channel)
		{
			channel = new Channel(name, password);

			server->registerChannel(channel);

			channel->addClient(client);
			channel->addOperator(client);

			std::string users = "";
			std::vector<std::string> nicknames = channel->getNicknames();
			std::vector<std::string>::iterator it = nicknames.begin();

			while (it != nicknames.end())
			{
				users.append(*it + " ");
				++it;
			}

			client->write(":" + client->getPrefix() + " JOIN " + channel->getName() + "\r\n");
			client->write(":ft_irc.server MODE " + channel->getName() + " +t\r\n");
			client->write(":ft_irc.server 353 " + client->getNickname() + " = " + channel->getName() + " :" + users + "\r\n");
			client->write(":ft_irc.server 366 " + client->getNickname() + " " + channel->getName() + " :End of /NAMES list.\r\n");

			channel->broadcast(":" + client->getPrefix() + " JOIN " + channel->getName() + "\r\n", client);

			return;
		}

		if (channel->getLimit() > 0 && channel->getClients().size() >= channel->getLimit())
		{
			client->write(":ft_irc.server 471 " + client->getNickname() + " " + name + " :Cannot join channel (+l)\r\n");
			return;
		}
		if (!channel->getK().empty())
		{
			if (password.empty() || channel->getK() != password)
			{
				client->write(":ft_irc.server 475 " + client->getNickname() + " " + name + " :Cannot join channel (+k) - bad key\r\n");
				return;
			}
		}
		if (channel->isInviteOnly() && !channel->isInvited(client))
		{
			client->write(":ft_irc.server 473 " + client->getNickname() + " " + name + " :Cannot join channel (+i) - you must be invited\r\n");
			return;
		}

		channel->addClient(client);

		std::string users = "";
		std::vector<std::string> nicknames = channel->getNicknames();
		std::vector<std::string>::iterator it = nicknames.begin();

		while (it != nicknames.end())
		{
			users.append(*it + " ");
			++it;
		}

		client->write(":" + client->getPrefix() + " JOIN " + channel->getName() + "\r\n");

		if (channel->getTopic().empty())
		{
			client->write(":ft_irc.server 331 " + client->getNickname() + " " + channel->getName() + " :No topic is set\r\n");
		}
		else
		{
			client->write(":ft_irc.server 332 " + client->getNickname() + " " + channel->getName() + " :" + channel->getTopic() + "\r\n");
		}

		client->write(":ft_irc.server 353 " + client->getNickname() + " = " + channel->getName() + " :" + users + "\r\n");
		client->write(":ft_irc.server 366 " + client->getNickname() + " " + channel->getName() + " :End of /NAMES list.\r\n");

		channel->broadcast(":" + client->getPrefix() + " JOIN " + channel->getName() + "\r\n", client);
	}
}
