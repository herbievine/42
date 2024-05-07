/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 13:10:12 by codespace        ###   ########.fr       */
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

static AForm *makeShrubberyCreationForm(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

static AForm *makeRobotomyRequestForm(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

static AForm *makePresidentialPardonForm(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) const
{
	const int FORM_COUNT = 3;

	const std::string formAliases[FORM_COUNT] = {
			"shrubbery creation",
			"robotomy request",
			"presidential pardon"};

	AForm *(*forms[FORM_COUNT])(const std::string &target) = {
			makeShrubberyCreationForm,
			makeRobotomyRequestForm,
			makePresidentialPardonForm};

	for (int i = 0; i < FORM_COUNT; i++)
	{
		if (name == formAliases[i])
		{
			std::cout << "Intern creates " << name << std::endl;
			return forms[i](target);
		}
	}

	std::cerr << "Intern could not create " << name << " form" << std::endl;

	return nullptr;
}
