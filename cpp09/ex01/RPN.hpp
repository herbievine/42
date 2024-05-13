/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/13 08:43:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>

class RPN
{
public:
	explicit RPN();
	RPN(const RPN &src);
	~RPN();

	RPN &operator=(const RPN &rhs);

	double expr(const std::string &str);

	class InvalidOperationException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Invalid operation";
		}
	};

	class DivisionByZeroException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Division by zero";
		}
	};

private:
	std::stack<int> _nums;
};
