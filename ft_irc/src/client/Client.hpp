/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/07/01 15:27:19 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Client
{
public:
	explicit Client(int fd, std::string ip);
	Client(const Client &src);
	~Client();

	Client &operator=(const Client &rhs);

	int getFd() const;

private:
	int _fd;
	std::string _ip;
};

std::ostream &operator<<(std::ostream &o, const Client &Client);
