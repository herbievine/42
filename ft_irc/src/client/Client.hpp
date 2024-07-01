/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/07/01 17:35:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define RPL_WELCOME(source) "001 " + source + " :Welcome " + source + " to the ft_irc network"

class Client
{
public:
	explicit Client(int fd, std::string ip, std::string hostname);
	Client(const Client &src);
	~Client();

	Client &operator=(const Client &rhs);

	void reply(const std::string &msg) const;

	int getFd() const { return _fd; }
	std::string getNickname() const { return _nickname; }

private:
	int _fd;
	std::string _ip;
	std::string _hostname;

	std::string _username = "username";
	std::string _realname = "realname";
	std::string _nickname = "nickname";
};
