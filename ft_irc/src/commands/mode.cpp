#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"
#include "../utils/utils.hpp"

void mode(Server *server, Client *client, std::vector<std::string> const &args)
{
	if (args.empty() || args.size() < 2)
	{
		client->write(":ft_irc.server 461 " + client->getNickname() + " MODE :Not enough parameters\r\n");
		return;
	}

	std::string name = args[0];

	std::vector<std::string> params;

	for (int i = 2; i < args.size(); i++)
		params.push_back(args[i]);

	Channel *channel = server->getChannel(name);

	if (!channel)
	{
		client->write(":ft_irc.server 403 " + client->getNickname() + " " + name + " :No such channel\r\n");
		return;
	}

	bool isPositive;
	for (int i = 0; i < args[1].size(); i++)
	{
	    if (args[1][i + 1] && (args[1][i] == '-' || args[1][i] == '+') && (args[1][i + 1] == '-' || args[1][i + 1] == '+'))
    	{
    	    client->write(":ft_irc.server 501 " + client->getNickname() + " MODE :Unknown MODE flag 🇧🇷\r\n");
            return;
    	}
		if (args[1][i] == '+')
			isPositive = true;
		else if (args[1][i] == '-')
			isPositive = false;
		else if (args[1][i] == 'i')
		{
			if (!channel->isOperator(client))
			{
				client->write(":ft_irc.server 482 " + client->getNickname() + " " + name + " :You're not channel operator\r\n");
				return;
			}

			if (isPositive)
				channel->setInviteOnly(true);
			else
				channel->setInviteOnly(false);
			channel->broadcast(":" + client->getPrefix() + " MODE " + name + (isPositive ? " +i" : " -i") + "\r\n");
		}
		else if (args[1][i] == 't')
		{
			if (isPositive)
				channel->setTopicPrivilege(true);
			else
				channel->setTopicPrivilege(false);
			channel->broadcast(":" + client->getPrefix() + " MODE " + name + (isPositive ? " +t" : " -t") + "\r\n");
		}
		else if (args[1][i] == 'o')
		{
			if (params.empty())
			{
				client->write(":ft_irc.server 461 " + client->getNickname() + " MODE :Not enough parameters\r\n");
				return;
			}
			else if (!channel->isOperator(client))
			{
				client->write(":ft_irc.server 482 " + client->getNickname() + " " + name + " :You're not channel operator\r\n");
				return;
			}

			const Client *ClientTarget = channel->getClientByNickname(params[0]);

			if (!ClientTarget)
			{
				client->write(":ft_irc.server 441 " + client->getNickname() + " " + name + " :They aren't on that channel\r\n");
				return;
			}

			if (isPositive)
				channel->addOperator(ClientTarget);
			else
				channel->removeOperator(ClientTarget);

			channel->broadcast(":" + client->getPrefix() + " MODE " + name + (isPositive ? " +o " : " -o ") + params[0] + "\r\n");
			params.erase(params.begin());
		}
		else if (args[1][i] == 'k')
		{
			if (params.empty() && isPositive)
			{
				client->write(":ft_irc.server 461 " + client->getNickname() + " MODE :Not enough parameters\r\n");
				return;
			}
			else if (!channel->isOperator(client))
			{
				client->write(":ft_irc.server 482 " + client->getNickname() + " " + name + " :You're not channel operator\r\n");
				return;
			}

			if (isPositive)
				channel->setK(params[0]);
			else
				channel->setK("");
			if (isPositive)
				channel->broadcast(":" + client->getPrefix() + " MODE " + name + " +k " + params[0] + "\r\n");
			else if (!isPositive && params.size() > 0)
				channel->broadcast(":" + client->getPrefix() + " MODE " + name + " -k *\r\n");
			if (params.size() > 0)
				params.erase(params.begin());
		}
	}
}
