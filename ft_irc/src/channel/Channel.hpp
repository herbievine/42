/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/12 16:03:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

void pass(Client *client, std::vector<std::string> const &args);
void nick(Client *client, std::vector<std::string> const &args);

class Channel
{
public:
	explicit Channel(std::string &name, std::string &password, Client *admin);
	Channel(const Channel &src);
	~Channel();

	Channel &operator=(const Channel &rhs);

	std::string getName() const { return _name; }
	Client *getAdmin() const { return _admin; }
	std::vector<Client *> getClients() const { return _clients; }

	void setName(std::string name) { _name = name; }
	void setAdmin(Client *admin) { _admin = admin; }

	void addClient(Client *);

private:
	std::string _name;
	Client *_admin;
	std::vector<Client *> _clients;

	// Channel key (password)
	std::string _k;
	// Channel limit
	size_t _l;
};
