/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:20 by herbie            #+#    #+#             */
/*   Updated: 2024/05/04 10:13:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(const std::string &name, const int gradeToSign, const int gradeToExec)
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
	this->gradeToSign = rhs.getGradeToSign();
	this->gradeToExec = rhs.getGradeToExec();
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
