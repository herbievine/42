/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:17:01 by herbie            #+#    #+#             */
/*   Updated: 2024/04/12 09:52:30 by herbie           ###   ########.fr       */
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
	explicit Form(const std::string &name, int gradeToSign, int gradeToExec);
	Form(const Form &form);
	~Form();

	Form &operator=(const Form &rhs);

	const std::string &getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExec() const;

	void beSigned(const Bureaucrat &bureaucrat);

	friend std::ostream &operator<<(std::ostream &o, const Form &form);

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

private:
	std::string name;
	bool isSigned;
	int gradeToSign;
	int gradeToExec;
};

#endif /* FORM_HPP */
