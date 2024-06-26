/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:23 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 12:17:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat bureaucrat("Dylan", 70);
		Form formA("Form 16A", 80, 55);
		Form formB("Form 16B", 65, 35);

		std::cout << bureaucrat << std::endl;

		std::cout << formA << std::endl;
		std::cout << formB << std::endl;

		formA.beSigned(bureaucrat);
		bureaucrat.signForm(formB);

		std::cout << formA << std::endl;
		std::cout << formB << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}
