/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 12:26:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(int grade) : name("John")
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();

	this->grade = grade;
}

Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();

	this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &src)
{
	*this = src;
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs)
{
	return *this;
}

const std::string &Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

// cppcheck-suppress unusedFunction
void Bureaucrat::incrementGrade()
{
	if (grade == 1)
		throw GradeTooHighException();
	grade--;
}

// cppcheck-suppress unusedFunction
void Bureaucrat::decrementGrade()
{
	if (grade == 150)
		throw GradeTooLowException();
	grade++;
}

void Bureaucrat::signForm(AForm &form)
{
	try
	{
		form.beSigned(*this);
		std::cout << *this << " signed " << form.getName() << std::endl;
	}
	catch (AForm::GradeTooLowException &e)
	{
		std::cerr << *this << " coulnd't sign " << form.getName() << " because his grade is too low" << std::endl;
	}
}

void Bureaucrat::executeForm(const AForm &form)
{
	try
	{
		form.execute(*this);
		std::cout << *this << " executed " << form.getName() << std::endl;
	}
	catch (AForm::NotSignedException &e)
	{
		std::cerr << *this << " coulnd't execute " << form.getName() << " because it hasn't been signed" << std::endl;
	}
	catch (AForm::GradeTooLowException &e)
	{
		std::cerr << *this << " coulnd't execute " << form.getName() << " because his grade is too low" << std::endl;
	}
}

std::ostream &operator<<(std::ostream &o, Bureaucrat const &i)
{
	o << i.getName() << ", bureaucrat grade " << i.getGrade();
	return o;
}
