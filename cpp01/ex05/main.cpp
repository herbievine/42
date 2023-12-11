/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 16:54:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	std::string input;
	Harl harl;

	do
	{
		std::cout << "Enter a level: ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			break;
		harl.complain(input);
	} while (input.compare("exit"));

	return 0;
}
