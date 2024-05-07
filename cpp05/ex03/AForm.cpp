/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:20 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 12:30:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(const std::string &name, const int gradeToSign, const int gradeToExec) : name(name), gradeToSign(gradeToSign), gradeToExec(gradeToExec)
{
	if (gradeToSign < 1 || gradeToExec < 1)
		throw GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExec > 150)
		throw GradeTooLowException();

	this->isSigned = false;
}

AForm::AForm(const AForm &src) : name(src.getName()), gradeToSign(src.getGradeToSign()), gradeToExec(src.getGradeToExec())
{
	*this = src;
}

AForm::~AForm()
{
}

AForm &AForm::operator=(const AForm &rhs)
{
	return *this;
}

const std::string &AForm::getName() const
{
	return this->name;
}

bool AForm::getIsSigned() const
{
	return this->isSigned;
}

const int AForm::getGradeToSign() const
{
	return this->gradeToSign;
}

const int AForm::getGradeToExec() const
{
	return this->gradeToExec;
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > this->getGradeToSign())
		throw GradeTooLowException();

	this->isSigned = true;
}

std::ostream &operator<<(std::ostream &o, const AForm &i)
{
	o << i.getName() << " is " << (i.getIsSigned() ? "" : "not ") << "signed.";
	return o;
}
