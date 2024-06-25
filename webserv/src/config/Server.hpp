/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 11:40:51 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iostream"

class Server
{
public:
	explicit Server();
	Server(const Server &src);
	~Server();

	Server &operator=(const Server &rhs);

	std::string getName() const;
	std::string getHost() const;
	int getPort() const;
	std::string getRoot() const;
	std::vector<std::string> getIndexes() const;
	std::vector<std::string> getMethods() const;

	void setName(std::string name);
	void setHost(std::string host);
	void setPort(int port);
	void setRoot(std::string root);
	void addIndex(std::string index);
	void addMethod(std::string method);

private:
	std::string _name;
	std::string _host;
	int _port;
	std::string _root;
	std::vector<std::string> _indexes;
	std::vector<std::string> _methods;
};

std::ostream &operator<<(std::ostream &o, const Server &server);
