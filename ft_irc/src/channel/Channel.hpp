/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/24 11:08:26 by herbie           ###   ########.fr       */
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
	void Channel::broadcast(std::string message, Client *exclude);

	std::string getName() const { return _name; }
	std::vector<Client *> getClients() const { return _clients; }
	std::vector<std::string> getNicknames() const;
	bool isOperator(Client *client) const;

	std::string getKey() const { return _key; }
	size_t getLimit() const { return _limit; }

	void setName(std::string name) { _name = name; }

	void setKey(std::string key) { _key = key; }
	void setLimit(size_t limit) { _limit = limit; }

	void addClient(Client *client);
	void removeClient(Client *client);

	void addOperator(Client *client);
	void removeOperator(Client *client);

private:
	Channel(const Channel &src);

	std::string _name;
	std::vector<Client *> _clients;
	std::map<std::string, bool> _operators;

	std::string _key; // aka password
	size_t _limit;
};

#endif /* CHANNEL_HPP */
