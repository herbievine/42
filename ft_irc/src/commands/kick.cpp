#include "../client/Client.hpp"
#include "../server/Server.hpp"

void kick(Server *server, Client *client, std::vector<std::string> const &args)
{
	std::string channelName;
	std::string nickname;
	std::string reason;

	std::cout << "kick command" << std::endl;

	if (args.size() < 2)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"));
		return;
	}

	std::cout << "set kick value" << std::endl;
	channelName = args[0];
	nickname = args[1];
	reason = args[2];

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

	Client *target = channel->getClientByNickname(nickname);
	if (target == nullptr)
	{
		client->reply(ERR_NOSUCHNICK(client->getNickname(), nickname));
		return;
	}

	channel->removeClient(target);
	target->reply(":" + client->getNickname() + " KICK " + channelName + " " + nickname + " :" + reason);

	// TODO: send kick message to all clients in the channel
}
// TODO: error: can't receive the messages from the channel but can send messages to the channel