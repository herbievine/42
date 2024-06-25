/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:18:58 by herbie            #+#    #+#             */
/*   Updated: 2024/06/25 10:24:29 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/Config.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: please provide a config file" << std::endl;
		return 1;
	}

	Config config(argv[1]);

	config.parse();

	// std::cout << "Tokens:" << std::endl;

	// std::vector<std::string>::iterator it = tokens.begin();

	// while (it != tokens.end())
	// {
	// 	std::cout << *it << std::endl;
	// 	it++;
	// }

	return 0;
}
