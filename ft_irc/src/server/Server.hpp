/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/09/05 14:22:42 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_CHANNEL_COUNT_PER_CLIENT 10

#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>

class Server;
class Channel;

void cap(Server *server, Client *client, std::vector<std::string> const &args);
void join(Server *server, Client *client, std::vector<std::string> const &args);
void kick(Server *server, Client *client, std::vector<std::string> const &args);
void mode(Server *server, Client *client, std::vector<std::string> const &args);
void nick(Server *server, Client *client, std::vector<std::string> const &args);
void part(Server *server, Client *client, std::vector<std::string> const &args);
void pass(Server *server, Client *client, std::vector<std::string> const &args);
void ping(Server *server, Client *client, std::vector<std::string> const &args);
void pong(Server *server, Client *client, std::vector<std::string> const &args);
void privmsg(Server *server, Client *client, std::vector<std::string> const &args);
void quit(Server *server, Client *client, std::vector<std::string> const &args);
void topic(Server *server, Client *client, std::vector<std::string> const &args);
void user(Server *server, Client *client, std::vector<std::string> const &args);
void who(Server *server, Client *client, std::vector<std::string> const &args);
void invite(Server *server, Client *client, std::vector<std::string> const &args);

class Server
{
public:
	explicit Server(const std::string &port, std::string &password);
	~Server();

	void start();

	void acceptConnection();
	void readFromClient(int fd);

	void disconnectClient(int fd, const std::string reason);

	std::string getPassword() const { return _password; }

	void registerChannel(Channel *channel);
	Channel *getChannel(std::string &name);
	void deleteChannel(Channel *channel);

	Client *getClientByNickname(const std::string &nickname);

	static bool stop;
	static void handleSignal(int signal);

private:
	Server(const Server &src);

	Server &operator=(const Server &rhs);

	int _port;
	int _lsd; // Listen Socket Descriptor
	std::string _password;
	std::vector<struct pollfd> _fds;

	std::map<std::string, Channel *> _channels;
	std::map<int, Client *> _clients;
};

#endif /* SERVER_HPP */
