/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:21:54 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 10:12:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>

class Config
{
public:
	explicit Config(std::string path);
	Config(const Config &src);
	~Config();

	Config &operator=(const Config &rhs);

	void parse() const;

private:
	std::vector<std::string> _tokens;
	std::vector<Server> _servers;
};
