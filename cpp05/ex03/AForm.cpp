/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:20 by herbie            #+#    #+#             */
/*   Updated: 2024/04/22 07:57:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExec)
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

AForm::AForm(const AForm &form)
{
	*this = form;
}

AForm::~AForm()
{
}

AForm &AForm::operator=(const AForm &rhs)
{
	this->name = rhs.name;
	this->isSigned = rhs.isSigned;
	this->gradeToSign = rhs.gradeToSign;
	this->gradeToExec = rhs.gradeToExec;
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

int AForm::getGradeToSign() const
{
	return this->gradeToSign;
}

// cppcheck-suppress unusedFunction
int AForm::getGradeToExec() const
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
