#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"

void privmsg(Server *server, Client *client, std::vector<std::string> const &args)
{
	std::string target;
	std::string message;

	if (args.size() < 2)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
		return;
	}

	target = args[0];
	std::vector<std::string>::const_iterator it = args.begin();
	for (size_t i = 1; i < args.size(); ++i)
	{
		message.append(args[i] + " ");
	}

	if (!message.empty())
	{
		message.pop_back();
	}

	Channel *channel = server->getChannel(target);

	if (channel)
	{
		std::vector<Client *> clients = channel->getClients();
		for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			std::cout << ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n"
								<< std::endl;
			if (*it != client)
			{
				(*it)->sendRaw(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
			}
		}
	}
	else
	{
		if (!client->getChannel())
		{
			client->reply(ERR_NOSUCHNICK(client->getNickname(), target));
			return;
		}
		channel = client->getChannel();
		Client *ClientTarget = channel->getClientByNickname(target);
		if (!ClientTarget)
		{
			client->reply(ERR_NOSUCHNICK(client->getNickname(), target));
		}
		else
		{
			ClientTarget->sendRaw(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n");
		}
	}
}
