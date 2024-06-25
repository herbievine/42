/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigReader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 09:56:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigReader.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

ConfigReader::ConfigReader()
{
}

ConfigReader::ConfigReader(const ConfigReader &src)
{
}

ConfigReader::~ConfigReader()
{
}

ConfigReader &ConfigReader::operator=(const ConfigReader &rhs)
{
	if (this != &rhs)
	{
	}

	return *this;
}

std::vector<std::string> ConfigReader::read(std::string path) const
{
	std::vector<std::string> tokens;
	std::ifstream cfn;

	cfn.open(path);

	if (!cfn.is_open())
	{
		std::cerr << "Error: Could not open file" << std::endl;
		exit(1);
	}

	std::string line;
	while (std::getline(cfn, line))
	{
		int len = line.length();

		if (len == 0 || line[0] == '#')
			continue;

		std::string token = "";

		for (int i = 0; i < len; i++)
		{
			if (std::isspace(line[i]) && token.length() == 0)
				continue;
			else if (std::isspace(line[i]) && token.length() > 0)
			{
				tokens.push_back(token);
				token = "";
			}
			else
				token += line[i];
		}

		if (token.length() > 0)
			tokens.push_back(token);
	}

	cfn.close();

	return tokens;
}
