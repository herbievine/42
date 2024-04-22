/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2024/04/22 10:10:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &src)
{
	*this = src;
}

Intern::~Intern()
{
}

Intern &Intern::operator=(const Intern &rhs)
{
	(void)rhs;
	return *this;
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const
{
	const int supportedForms = 3;

	std::string formAliases[supportedForms] = {
			"shrubbery creation",
			"robotomy request",
			"presidential pardon"};

	AForm *forms[supportedForms] = {
			new ShrubberyCreationForm(target),
			new RobotomyRequestForm(target),
			new PresidentialPardonForm(target)};

	for (int i = 0; i < supportedForms; i++)
	{
		if (name == formAliases[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			return forms[i];
		}
	}

	std::cerr << "Intern could not create " << name << " form" << std::endl;

	return nullptr;
}
