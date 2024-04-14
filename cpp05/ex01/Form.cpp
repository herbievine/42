/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:20 by herbie            #+#    #+#             */
/*   Updated: 2024/04/12 10:15:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(const std::string &name, int gradeToSign, int gradeToExec)
{
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();

	this->name = name;
	this->isSigned = false;
	this->gradeToSign = gradeToSign;

	if (gradeToSign > gradeToExec)
		this->gradeToExec = gradeToExec;
	else
		this->gradeToExec = gradeToSign;
}

Form::Form(const Form &form)
{
	*this = form;
}

Form::~Form()
{
}

Form &Form::operator=(const Form &rhs)
{
	this->name = rhs.name;
	this->isSigned = rhs.isSigned;
	this->gradeToSign = rhs.gradeToSign;
	this->gradeToExec = rhs.gradeToExec;
	return *this;
}

const std::string &Form::getName() const
{
	return this->name;
}

bool Form::getIsSigned() const
{
	return this->isSigned;
}

int Form::getGradeToSign() const
{
	return this->gradeToSign;
}

// cppcheck-suppress unusedFunction
int Form::getGradeToExec() const
{
	return this->gradeToExec;
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->getGradeToSign())
		throw GradeTooLowException();

	this->isSigned = true;
}

std::ostream &operator<<(std::ostream &o, const Form &i)
{
	o << i.getName() << " is " << (i.getIsSigned() ? "" : "not ") << "signed.";
	return o;
}
