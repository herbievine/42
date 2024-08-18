/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 17:30:04 by herbie           ###   ########.fr       */
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
	explicit Channel(std::string &name, std::string &password, Client *admin);
	~Channel();

	Channel &operator=(const Channel &rhs);

	void broadcast(std::string message);

	std::string getName() const { return _name; }
	Client *getAdmin() const { return _admin; }
	std::vector<Client *> getClients() const { return _clients; }
	std::vector<std::string> getNicknames() const;

	std::string getKey() const { return _key; }
	size_t getLimit() const { return _limit; }

	void setName(std::string name) { _name = name; }
	void setAdmin(Client *admin) { _admin = admin; }

	void setKey(std::string key) { _key = key; }
	void setLimit(size_t limit) { _limit = limit; }

	void addClient(Client *);

private:
	Channel(const Channel &src);

	std::string _name;
	Client *_admin;
	std::vector<Client *> _clients;

	std::string _key; // aka password
	size_t _limit;
};

#endif /* CHANNEL_HPP */
