/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:17:01 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 12:02:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
public:
	explicit Form(const std::string &name, const int gradeToSign, const int gradeToExec);
	Form(const Form &src);
	~Form();

	Form &operator=(const Form &rhs);

	const std::string &getName() const;
	bool getIsSigned() const;
	const int getGradeToSign() const;
	const int getGradeToExec() const;

	void beSigned(const Bureaucrat &bureaucrat);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Grade is too high";
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Grade is too low";
		}
	};

private:
	const std::string name;
	bool isSigned;
	const int gradeToSign;
	const int gradeToExec;
};

std::ostream &operator<<(std::ostream &o, const Form &form);

#endif /* FORM_HPP */
