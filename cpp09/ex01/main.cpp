/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/13 10:24:52 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	try
	{
		RPN rpn;

		double res = rpn.expr(argv[1]);

		std::cout << res << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}
