/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/08/18 20:57:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../channel/Channel.hpp"
#include <iostream>

class Channel;

#define RPL_WELCOME(source) "001 " + source + " :Welcome " + source + " to the ft_irc network"

#define RPL_NAMREPLY(source, channel, users) "353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel) "366 " + source + " " + channel + " :End of /NAMES list."

#define ERR_NOSUCHNICK(source, nickname) "401 " + source + " " + nickname + " :No such nick/channel"
#define ERR_NOSUCHCHANNEL(source, channel) "403 " + source + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(source, channel) "404 " + source + " " + channel + " :Cannot send to channel"
#define ERR_TOOMANYCHANNELS(source, channel) "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_UNKNOWNCOMMAND(source, command) "421 " + source + " " + command + " :Unknown command"
#define ERR_NONICKNAMEGIVEN(source) "431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source) "433 " + source + " " + source + " :Nickname is already in use"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(source, channel) "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_NOTREGISTERED(source) "451 " + source + " :You have not registered"
#define ERR_NEEDMOREPARAMS(source, command) "461 " + source + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(source) "462 " + source + " :You may not register"
#define ERR_PASSWDMISMATCH(source) "464 " + source + " :Password is incorrect"
#define ERR_CHANNELISFULL(source, channel) "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY(source, channel) "475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_CHANOPRIVSNEEDED(source, channel) "482 " + source + " " + channel + " :You're not channel operator"

#define RPL_JOIN(source, channel) ":" + source + " JOIN :" + channel
#define RPL_PART(source, channel) ":" + source + " PART :" + channel
#define RPL_PING(source, token) ":" + source + " PONG :" + token
#define RPL_PRIVMSG(source, target, message) ":" + source + " PRIVMSG " + target + " :" + message
#define RPL_NOTICE(source, target, message) ":" + source + " NOTICE " + target + " :" + message
#define RPL_QUIT(source, message) ":" + source + " QUIT :Quit: " + message
#define RPL_KICK(source, channel, target, reason) ":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_MODE(source, channel, modes, args) ":" + source + " MODE " + channel + " " + modes + " " + args

class Client
{
public:
	explicit Client();
	explicit Client(int fd, std::string ip, std::string hostname);
	Client(const Client &src);
	~Client();

	Client &operator=(const Client &rhs);

	void reply(const std::string &msg) const;
	void sendRaw(const std::string &msg) const;
	void joinChannel(Channel *channel);

	int getFd() const { return _fd; }

	std::string getUsername() const { return _username; }
	std::string getRealname() const { return _realname; }
	std::string getNickname() const { return _nickname; }
	bool isRegistered() const { return _isRegistered; }
	bool hasBeenWelcomed() const { return _hasBeenWelcomed; }

	Channel *getChannel() const { return _channel; }
	bool isChannelOperator() const { return _isChannelOperator; }

	std::string getPrefix() const;

	void authenticate() { _auth = true; }

	void setNickname(const std::string &nickname) { _nickname = nickname; }
	void setUsername(const std::string &username) { _username = username; }
	void setRealname(const std::string &realname) { _realname = realname; }
	void setIsRegistered(bool isRegistered) { _isRegistered = isRegistered; }
	void setHasBeenWelcomed(bool hasBeenWelcomed) { _hasBeenWelcomed = hasBeenWelcomed; }

	void setChannel(Channel *channel) { _channel = channel; }
	void setIsChannelOperator(bool isChannelOperator) { _isChannelOperator = isChannelOperator; }

private:
	int _fd;
	std::string _ip;
	std::string _hostname;

	bool _auth;

	std::string _username;
	std::string _realname;
	std::string _nickname;
	bool _isRegistered;
	bool _hasBeenWelcomed;

	Channel *_channel;
	bool _isChannelOperator;
};

#endif /* CLIENT_HPP */
