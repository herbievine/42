/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:52:37 by herbie           ###   ########.fr       */
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

	void broadcast(const std::string &message);
	void broadcast(const std::string &message, const Client *exclude);

	std::string getName() const { return _name; }
	std::vector<Client *> getClients() const { return _clients; }
	std::vector<std::string> getNicknames() const;
	bool isOperator(const Client *client) const;
	bool isClientInChannel(const Client *client) const;

	std::string getK() const { return _k; }
	bool getTopicPrivilege() const { return _topicPrivilege; }
	size_t getLimit() const { return _limit; }
	std::string getTopic() const { return _topic; }
	bool isInviteOnly() const { return _isInviteOnly; }
	bool isInvited(const Client *client);

	void setName(const std::string &name) { _name = name; }

	void setK(const std::string &k) { _k = k; }
	void setTopicPrivilege(bool topicPrivilege) { _topicPrivilege = topicPrivilege; }
	void setLimit(size_t limit) { _limit = limit; }
	void setTopic(const std::string &topic) { _topic = topic; }
	void setInviteOnly(bool isInviteOnly) { _isInviteOnly = isInviteOnly; }
	void setInvited(Client *client);

	void addClient(Client *client);
	void removeClient(const Client *client);

	void addOperator(const Client *client);
	void removeOperator(const Client *client);

	Client *getClientByNickname(const std::string &nickname);

private:
	Channel(const Channel &src);

	Channel &operator=(const Channel &rhs);

	std::string _name;
	std::vector<Client *> _clients;
	std::map<std::string, bool> _operators;
	std::vector<Client *> _invited;

	std::string _k; // aka password
	bool _isInviteOnly;
	bool _topicPrivilege; // aka topic protection for all user or only operator
	std::string _topic;
	size_t _limit;
};

#endif /* CHANNEL_HPP */
