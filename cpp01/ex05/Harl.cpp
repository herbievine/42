/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:24:46 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:11:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

Harl::Harl()
{
}

Harl::~Harl()
{
}

// cppcheck-suppress passedByValue
void Harl::complain(std::string level)
{
	int i;
	t_fn fn[4] = {
			&Harl::debug,
			&Harl::info,
			&Harl::warning,
			&Harl::error};
	std::string const levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (i = 0; i < 4; i++)
	{
		if (!level.compare(levels[i]))
			(this->*fn[i])();
	}
}

void Harl::debug(void)
{
	std::cout << "Debug level" << std::endl;
}

void Harl::info(void)
{
	std::cout << "Info level" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "Warning level" << std::endl;
}

void Harl::error(void)
{
	std::cout << "Error level" << std::endl;
}
