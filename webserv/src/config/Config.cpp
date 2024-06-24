/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/06/24 09:28:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "iostream"

Config::Config(std::string path) : _path(path)
{
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
		this->_path = rhs._path;
	}

	return *this;
}
