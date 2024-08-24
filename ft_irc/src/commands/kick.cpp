#include "../client/Client.hpp"
#include "../server/Server.hpp"

void kick(Server *server, Client *client, std::vector<std::string> const &args)
{
	std::string channelName;
	std::string nickname;
	std::string reason;

	if (args.size() < 2)
	{
		client->sendRaw(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK") + "\r\n");
		return;
	}

	channelName = args[0];
	nickname = args[1];
	reason = args[2];

	Channel *channel = server->getChannel(channelName);
	if (channel == nullptr)
	{
		client->sendRaw(ERR_NOSUCHCHANNEL(client->getNickname(), channelName) + "\r\n");
		return;
	}

	if (!channel->isOperator(client))
	{
		client->sendRaw(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName) + "\r\n");
		return;
	}

	Client *target = channel->getClientByNickname(nickname);
	if (target == nullptr)
	{
		client->sendRaw(ERR_NOSUCHNICK(client->getNickname(), nickname) + "\r\n");
		return;
	}

	channel->removeClient(target);
	channel->broadcast(RPL_KICK(client->getNickname(), channelName, target->getNickname(), reason + "\r\n"));
}