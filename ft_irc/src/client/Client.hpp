/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/26 15:55:20 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../channel/Channel.hpp"
#include <iostream>

class Channel;

enum AuthState
{
	UNAUTHENTICATED,
	AUTHENTICATED,
	REGISTERED,
};

class Client
{
public:
	explicit Client(int fd, std::string &ip, std::string &hostname);
	~Client();

	void reply(const std::string &msg) const;

	void write(const std::string &msg) const;

	int getFd() const { return _fd; }
	std::string getHostname() const { return _hostname; }

	std::string getUsername() const { return _username; }
	std::string getRealname() const { return _realname; }
	std::string getNickname() const { return _nickname; }

	Channel *getChannel() const { return _channel; }

	std::string getPrefix() const;

	AuthState getState() const { return _state; }
	void setState(AuthState state) { _state = state; }

	void setNickname(const std::string &nickname) { _nickname = nickname; }
	void setUsername(const std::string &username) { _username = username; }
	void setRealname(const std::string &realname) { _realname = realname; }

	void setChannel(Channel *channel) { _channel = channel; }

private:
	Client(const Client &src);

	Client &operator=(const Client &rhs);

	int _fd;
	std::string _ip;
	std::string _hostname;

	AuthState _state;

	std::string _username;
	std::string _realname;
	std::string _nickname;

	Channel *_channel;
};

#endif /* CLIENT_HPP */
