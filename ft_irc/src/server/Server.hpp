/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 14:51:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../client/Client.hpp"
#include "../channel/Channel.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <poll.h>

class Server;
class Channel;

void cap(const Client *client, std::vector<std::string> const &args);
void join(Server *server, Client *client, std::vector<std::string> const &args);
void kick(Server *server, const Client *client, std::vector<std::string> const &args);
void mode(Server *server, const Client *client, std::vector<std::string> const &args);
void nick(Server *server, Client *client, std::vector<std::string> const &args);
void part(Server *server, Client *client, std::vector<std::string> const &args);
void pass(const Server *server, Client *client, std::vector<std::string> const &args);
void ping(const Client *client, std::vector<std::string> const &args);
void pong(const Client *client, std::vector<std::string> const &args);
void privmsg(Server *server, Client *client, std::vector<std::string> const &args);
void quit(const Client *client, std::vector<std::string> const &args);
void topic(Server *server, const Client *client, std::vector<std::string> const &args);
void user(Client *client, std::vector<std::string> const &args);
void who(Server *server, const Client *client, std::vector<std::string> const &args);
void invite(Server *server, const Client *client, std::vector<std::string> const &args);

class Server
{
public:
	explicit Server(const std::string &port, std::string &password);
	~Server();

	void start();

	void acceptConnection();
	void readFromClient(int fd);

	void disconnectClient(int fd);

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

	std::unordered_map<std::string, Channel *> _channels;
	std::map<int, Client *> _clients;
};

#endif /* SERVER_HPP */
