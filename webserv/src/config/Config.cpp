/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 10:45:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "iostream"
#include <fstream>

Config::Config(std::string path)
{
	std::ofstream cfn;

	cfn.open(path);

	cfn.close();
}

Config::Config(const Config &src)
{
}

Config::~Config()
{
}

Config &Config::operator=(const Config &rhs)
{
	if (this != &rhs)
	{
		this->_serverName = rhs._serverName;
	}

	return *this;
}
