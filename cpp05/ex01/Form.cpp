/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:20 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 12:07:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(const std::string &name, const int gradeToSign, const int gradeToExec) : name(name), gradeToSign(gradeToSign), gradeToExec(gradeToExec)
{
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();

	this->isSigned = false;
}

Form::Form(const Form &src) : name(src.getName()), gradeToSign(src.getGradeToSign()), gradeToExec(src.getGradeToExec())
{
	*this = src;
}

Form::~Form()
{
}

Form &Form::operator=(const Form &rhs)
{
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

const int Form::getGradeToSign() const
{
	return this->gradeToSign;
}

const int Form::getGradeToExec() const
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
