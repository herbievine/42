/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 07:48:11 by codespace         #+#    #+#             */
/*   Updated: 2024/05/04 10:22:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("Robotomy Request Form", 72, 45), target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src) : AForm(src), target(src.target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	(void)rhs;
	return *this;
}

void RobotomyRequestForm::execute(const Bureaucrat &executor) const
{
	if (!getIsSigned())
		throw NotSignedException();
	if (executor.getGrade() > this->getGradeToExec())
		throw GradeTooLowException();

	// cppcheck-suppress unmatchedSuppression
	int rand;

	// cppcheck-suppress uninitvar
	if (rand % 2 == 0)
		std::cout << this->target << " has been robotomised" << std::endl;
	else
		std::cout << this->target << " has not been robotomised" << std::endl;
}
