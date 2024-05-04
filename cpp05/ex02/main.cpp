/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:23 by herbie            #+#    #+#             */
/*   Updated: 2024/05/04 09:31:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat bureaucrat("Dylan", 45);

		ShrubberyCreationForm form("garden");
		// RobotomyRequestForm form("my teacher");
		// PresidentialPardonForm form("my arse");

		std::cout << form << std::endl;

		bureaucrat.signForm(form);
		bureaucrat.executeForm(form);

		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}
