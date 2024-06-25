/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:22:42 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 13:12:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

Config::Config(std::string path)
{
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
		size_t len = line.length();

		if (len == 0 || line[0] == '#')
			continue;

		std::string token = "";

		for (size_t i = 0; i < len; i++)
		{
			if (std::isspace(line[i]) && token.length() == 0)
				continue;
			else if (std::isspace(line[i]) && token.length() > 0)
			{
				_tokens.push_back(token);
				token = "";
			}
			else if (line[i] == ';')
			{
				if (token.length() > 0)
					_tokens.push_back(token);

				_tokens.push_back(std::string(1, line[i]));
				token = "";
			}
			else
				token += line[i];
		}

		if (token.length() > 0)
			_tokens.push_back(token);
	}

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
		this->_servers = rhs._servers;
	}

	return *this;
}

void Config::parse() const
{
	for (size_t i = 0; i < _tokens.size(); i++)
	{
		if (_tokens[i] == "server")
		{
			if (i + 1 < _tokens.size() && _tokens[i + 1] != "{")
			{
				std::cerr << "Error: Expected `{` after `server` block" << std::endl;
				exit(1);
			}

			Server server;

			i += 2;

			while (i < _tokens.size() && _tokens[i] != "}")
			{
				if (_tokens[i] == "server_name")
				{
					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected value after `server_name`" << std::endl;
						exit(1);
					}
					else if (i + 2 >= _tokens.size() || _tokens[i + 2] != ";")
					{
						std::cerr << "Error: Expected `;` after `server_name` declaration" << std::endl;
						exit(1);
					}

					server.setName(_tokens[i + 1]);

					i += 2;
				}
				else if (_tokens[i] == "listen")
				{
					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected value after `listen`" << std::endl;
						exit(1);
					}
					else if (i + 2 >= _tokens.size() || _tokens[i + 2] != ";")
					{
						std::cerr << "Error: Expected `;` after `listen` declaration" << std::endl;
						exit(1);
					}

					std::string value = _tokens[i + 1];
					size_t colon = value.find(':');

					if (colon == std::string::npos)
					{
						try
						{
							server.setPort(std::stoi(value));
						}
						catch (const std::exception &e)
						{
							std::cerr << "Error: Invalid port" << std::endl;
							exit(1);
						}
					}
					else
					{
						server.setHost(value.substr(0, colon));

						try
						{
							server.setPort(std::stoi(value.substr(colon + 1)));
						}
						catch (const std::exception &e)
						{
							std::cerr << "Error: Invalid port" << std::endl;
							exit(1);
						}
					}

					i += 2;
				}
				else if (_tokens[i] == "root")
				{
					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected value after `root`" << std::endl;
						exit(1);
					}
					else if (i + 2 >= _tokens.size() || _tokens[i + 2] != ";")
					{
						std::cerr << "Error: Expected `;` after `root` declaration" << std::endl;
						exit(1);
					}

					server.setRoot(_tokens[i + 1]);

					i += 2;
				}
				else if (_tokens[i] == "index")
				{
					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected value after `index`" << std::endl;
						exit(1);
					}

					while (i + 1 < _tokens.size() && _tokens[i + 1] != ";")
					{
						server.addIndex(_tokens[i + 1]);
						i++;
					}

					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected `;` after `index` declaration" << std::endl;
						exit(1);
					}
				}
				else if (_tokens[i] == "allowed_methods")
				{
					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected value after `allowed_methods`" << std::endl;
						exit(1);
					}

					while (i + 1 < _tokens.size() && _tokens[i + 1] != ";")
					{
						server.addMethod(_tokens[i + 1]);
						i++;
					}

					if (i + 1 >= _tokens.size())
					{
						std::cerr << "Error: Expected `;` after `allowed_methods` declaration" << std::endl;
						exit(1);
					}
				}

				i++;
			}

			std::cout << server;
		}
	}
}
