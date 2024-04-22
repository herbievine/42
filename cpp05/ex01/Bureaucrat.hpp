/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2024/04/22 09:59:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat
{
public:
	explicit Bureaucrat(const std::string &name, int grade);
	Bureaucrat(const Bureaucrat &bureaucrat);
	~Bureaucrat();

	Bureaucrat &operator=(const Bureaucrat &rhs);

	const std::string &getName() const;
	int getGrade() const;
	void incrementGrade();
	void decrementGrade();

	void signForm(Form &form);

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Grade is too low";
		}
	};

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what()
		{
			return "Grade is too high";
		}
	};

private:
	int grade;
	std::string name;
};

std::ostream &operator<<(std::ostream &o, const Bureaucrat &i);

#endif /* BUREAUCRAT_HPP */
