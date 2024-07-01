/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/07/01 15:34:54 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../client/Client.hpp"
#include <iostream>
#include <vector>
#include <poll.h>

class Server
{
public:
	explicit Server(std::string port, std::string password);
	Server(const Server &src);
	~Server();

	Server &operator=(const Server &rhs);

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
	std::vector<Client> _clients;
};
