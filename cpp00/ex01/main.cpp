/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:14:48 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 12:27:23 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"
#include <iostream>

int main()
{
	std::string command;
	PhoneBook phoneBook;
	phoneBook.count = 0;
	phoneBook.length = 0;

	while (true)
	{
		std::cout << "Enter command: ";
		std::getline(std::cin, command);
		if (std::cin.eof())
			break;
		else if (command == "EXIT")
			break;
		else if (command == "ADD")
			phoneBook.add();
		else if (command == "SEARCH")
			phoneBook.search();
		else
			std::cout << "Invalid command" << std::endl;
	}
	return 0;
}
