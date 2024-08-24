#include "../client/Client.hpp"
#include "../server/Server.hpp"
#include "../channel/Channel.hpp"
#include "../utils/utils.hpp"

// TODO: add @ to a user +o

void mode(Server *server, Client *client, std::vector<std::string> const &args)
{
	std::string channelName;
	std::string mode;
	std::vector<std::string> parameters;
	bool isPositive = true;

	if (args.size() < 2)
	{
		client->sendRaw(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE") + "\r\n");
		return;
	}

	channelName = args[0];
	mode = args[1];

	for (int i = 2; i < args.size(); i++)
		parameters.push_back(args[i]);

	Channel *channel = server->getChannel(channelName);
	if (channel == nullptr)
	{
		client->sendRaw(ERR_NOSUCHCHANNEL(client->getNickname(), channelName) + "\r\n");
		return;
	}

	for (int i = 0; i < args[1].size(); i++)
	{
		if (args[1][i] == '+')
			isPositive = true;
		else if (args[1][i] == '-')
			isPositive = false;
		else if (args[1][i] == 'i')
		{
			if (!channel->isOperator(client))
			{
				client->sendRaw(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName) + "\r\n");
				return;
			}
			if (isPositive)
			{
				channel->setInviteOnly(true);
			}
			else
			{
				channel->setInviteOnly(false);
			}
		}
		else if (args[1][i] == 't')
		{
			if (isPositive)
				channel->setTopicPrivilege(true);
			else
				channel->setTopicPrivilege(false);
		}
		else if (args[1][i] == 'o')
		{
			if (parameters.empty())
			{
				client->sendRaw(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE") + "\r\n");
				return;
			}
			if (!channel->isOperator(client))
			{
				client->sendRaw(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName) + "\r\n");
				return;
			}
			Client *ClientTarget = channel->getClientByNickname(parameters[0]);
			if (!ClientTarget)
			{
				client->sendRaw(ERR_NOSUCHNICK(client->getNickname(), parameters[0]) + "\r\n");
				return;
			}
			if (isPositive)
				channel->addOperator(ClientTarget);
			else
				channel->removeOperator(ClientTarget);
			channel->broadcast(RPL_MODE(client->getPrefix(), channelName, (isPositive ? "+o" : "-o"), parameters[0]) + "\r\n");
			parameters.erase(parameters.begin());
		}
		else if (args[1][i] == 'k')
		{
			if (parameters.empty() && isPositive)
			{
				client->sendRaw(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE") + "\r\n");
				return;
			}
			if (!channel->isOperator(client))
			{
				client->sendRaw(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName) + "\r\n");
				return;
			}
			if (isPositive)
			{
				channel->setK(parameters[0]);
			}
			else
			{
				channel->setK(NULL);
			}
			channel->broadcast(RPL_MODE(client->getPrefix(), channelName, (isPositive ? "+k" : "-k"), (isPositive ? parameters[0] : "*")) + "\r\n");
			parameters.erase(parameters.begin());
		}
	}
}
