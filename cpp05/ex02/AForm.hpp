/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:17:01 by herbie            #+#    #+#             */
/*   Updated: 2024/05/04 10:00:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
public:
	explicit AForm(const std::string &name, const int gradeToSign, const int gradeToExec);
	AForm(const AForm &form);
	virtual ~AForm();

	AForm &operator=(const AForm &rhs);

	const std::string &getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExec() const;

	void beSigned(const Bureaucrat &bureaucrat);
	virtual void execute(const Bureaucrat &executor) const = 0;

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Grade is too high";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Grade is too low";
		}
	};

	class NotSignedException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Form is not signed";
		}
	};

private:
	std::string name;
	bool isSigned;
	int gradeToSign;
	int gradeToExec;
};

std::ostream &operator<<(std::ostream &o, const AForm &form);

#endif /* AFORM_HPP */
