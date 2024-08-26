/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 16:18:18 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../client/Client.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

class Client;

class Channel
{
public:
	explicit Channel(std::string &name, std::string &password);
	~Channel();

	Channel &operator=(const Channel &rhs);

	void broadcast(std::string message);
	void broadcast(std::string message, Client *exclude);

	std::string getName() const { return _name; }
	std::vector<Client *> getClients() const { return _clients; }
	std::vector<std::string> getNicknames() const;
	bool isOperator(Client *client) const;
	bool isClientInChannel(Client *client) const;

	std::string getK() const { return _k; }
	bool getTopicPrivilege() const { return _topicPrivilege; }
	size_t getLimit() const { return _limit; }
	std::string getTopic() const { return _topic; }
	bool isInviteOnly() const { return _isInviteOnly; }

	void setName(std::string name) { _name = name; }

	void setK(std::string k) { _k = k; }
	void setTopicPrivilege(bool topicPrivilege) { _topicPrivilege = topicPrivilege; }
	void setLimit(size_t limit) { _limit = limit; }
	void setTopic(std::string topic) { _topic = topic; }
	void setInviteOnly(bool isInviteOnly) { _isInviteOnly = isInviteOnly; }

	void addClient(Client *client);
	void removeClient(Client *client);

	void addOperator(Client *client);
	void removeOperator(Client *client);

	Client *getClientByNickname(std::string nickname);

private:
	Channel(const Channel &src);

	std::string _name;
	std::vector<Client *> _clients;
	std::map<std::string, bool> _operators;

	std::string _k; // aka password
	bool _isInviteOnly;
	bool _topicPrivilege; // aka topic protection for all user or only operator
	std::string _topic;
	size_t _limit;
};

#endif /* CHANNEL_HPP */
