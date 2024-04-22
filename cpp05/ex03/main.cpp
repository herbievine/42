/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:23 by herbie            #+#    #+#             */
/*   Updated: 2024/04/22 10:11:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat bureaucrat("Dylan", 10);
		Intern intern;

		AForm *form = intern.makeForm("presidential pardon", "my arse");

		if (!form)
			return 1;

		std::cout << *form << std::endl;

		bureaucrat.signForm(*form);
		bureaucrat.executeForm(*form);

		std::cout << *form << std::endl;

		delete form;
	}
	catch (AForm::GradeTooLowException &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	catch (AForm::GradeTooHighException &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}
