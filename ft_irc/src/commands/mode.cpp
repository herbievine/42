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
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
		return;
	}

	channelName = args[0];
	mode = args[1];

	for (int i = 2; i < args.size(); i++)
		parameters.push_back(args[i]);

	Channel *channel = server->getChannel(channelName);
	if (channel == nullptr)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
		return;
	}
	if (!channel->isOperator(client))
	{
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
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
			if (isPositive)
			{
				if (channel->isInviteOnly())
				{
					client->reply("Channel is already invite only");
					continue;
				}
				channel->setInviteOnly(true);
				client->reply("Channel is now in invite-only mode");
			}
			else
			{
				channel->setInviteOnly(false);
				client->reply("Channel is no longer in invite-only mode");
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
				client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
				return;
			}
			Client *client = channel->getClientByNickname(parameters[0]);
			if (client == nullptr)
			{
				client->reply(ERR_NOSUCHNICK(client->getNickname(), parameters[0]));
				return;
			}
			if (isPositive)
				channel->addOperator(client);
			else
				channel->removeOperator(client);
			parameters.erase(parameters.begin());
		}
		else if (args[1][i] == 'k')
		{
			if (parameters.empty() && isPositive)
			{
				client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
				return;
			}
			if (isPositive)
			{
				channel->setK(parameters[0]);
				parameters.erase(parameters.begin());
			}
			else
				channel->setK(NULL);
		}
	}
	if (!parameters.empty())
	{
		client->reply("too few paramters");
		return;
	}
}
