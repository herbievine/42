/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2024/04/11 14:55:01 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

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

	friend std::ostream &operator<<(std::ostream &o, const Bureaucrat &i);

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

#endif /* BUREAUCRAT_HPP */