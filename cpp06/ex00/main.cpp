/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/04 09:52:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ScalarConverter.hpp"

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		std::cout << "usage: ./convert <arg>" << std::endl;
		return 1;
	}

	try
	{
		ScalarConverter::convert(argv[1]);
	}
	catch (ScalarConverter::InvalidScalarException &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
