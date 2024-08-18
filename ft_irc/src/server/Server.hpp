/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 20:53:25 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

class Server;

void cap(Client *client, std::vector<std::string> const &args);
void join(Server *server, Client *client, std::vector<std::string> const &args);
void nick(Client *client, std::vector<std::string> const &args);
void pass(Client *client, std::vector<std::string> const &args);
void ping(Client *client, std::vector<std::string> const &args);
void pong(Client *client, std::vector<std::string> const &args);
void quit(Client *client, std::vector<std::string> const &args);
void user(Client *client, std::vector<std::string> const &args);

class Server
{
public:
	explicit Server(std::string port, std::string password);
	Server(const Server &src);
	~Server();

	Server &operator=(const Server &rhs);

	void createChannel(std::string name, std::string password, Client *admin);

	Channel *getChannel(std::string name);

	void start();

	void acceptConnection();
	void readFromClient(int fd);

	void disconnectClient(int fd);

	static bool stop;
	static void handleSignal(int signal);

private:
	int _port;
	int _lsd; // Listen Socket Descriptor
	std::vector<struct pollfd> _fds;
	std::vector<Channel *> _channels;
	std::map<int, Client *> _clients;
};

#endif /* SERVER_HPP */
