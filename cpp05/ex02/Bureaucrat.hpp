/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2024/05/07 11:59:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include "AForm.hpp"

class AForm;

class Bureaucrat
{
public:
	explicit Bureaucrat(int grade);
	explicit Bureaucrat(const std::string &name, int grade);
	Bureaucrat(const Bureaucrat &src);
	~Bureaucrat();

	Bureaucrat &operator=(const Bureaucrat &rhs);

	const std::string &getName() const;
	int getGrade() const;

	void incrementGrade();
	void decrementGrade();

	void signForm(AForm &form);
	void executeForm(const AForm &form);

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Grade is too low";
		}
	};

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Grade is too high";
		}
	};

private:
	const std::string name;
	int grade;
};

std::ostream &operator<<(std::ostream &o, const Bureaucrat &i);

#endif /* BUREAUCRAT_HPP */
