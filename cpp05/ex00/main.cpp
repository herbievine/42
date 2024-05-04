/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:23 by herbie            #+#    #+#             */
/*   Updated: 2024/05/04 09:31:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <iostream>

int main(void)
{
	try
	{
		Bureaucrat bureaucrat("Dylan", 1);

		std::cout << bureaucrat << std::endl;

		bureaucrat.incrementGrade();
		bureaucrat.incrementGrade();
		bureaucrat.decrementGrade();

		std::cout << "getName(): " << bureaucrat.getName() << std::endl;
		std::cout << "getGrade(): " << bureaucrat.getGrade() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
}
