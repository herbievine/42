/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/13 10:31:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <fstream>

RPN::RPN()
{
}

RPN::RPN(const RPN &src)
{
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &rhs)
{
	return *this;
}

double RPN::expr(const std::string &str)
{
	double r = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		char c = str[i];

		if (c == ' ')
			continue;
		else if (isdigit(c))
		{
			_nums.push(c - '0');
			continue;
		}

		if (_nums.size() < 2)
			throw InvalidOperationException();

		if (c == '+')
		{
			int right = _nums.top();
			_nums.pop();
			int left = _nums.top();
			_nums.pop();

			std::cout << left << "+" << right << std::endl;

			_nums.push(left + right);
		}
		else if (c == '-')
		{
			int right = _nums.top();
			_nums.pop();
			int left = _nums.top();
			_nums.pop();

			std::cout << left << "-" << right << std::endl;

			_nums.push(left - right);
		}
		else if (c == '*')
		{
			int right = _nums.top();
			_nums.pop();
			int left = _nums.top();
			_nums.pop();

			std::cout << left << "*" << right << std::endl;

			_nums.push(left * right);
		}
		else if (c == '/')
		{
			int right = _nums.top();
			_nums.pop();
			int left = _nums.top();
			_nums.pop();

			if (right == 0)
				throw DivisionByZeroException();

			std::cout << left << "/" << right << std::endl;

			_nums.push(left / right);
		}
		else
			throw InvalidOperationException();
	}

	return _nums.top();
}
