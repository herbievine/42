/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/07 09:22:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

class Span
{
public:
	explicit Span();
	explicit Span(unsigned int n);
	Span(const Span &src);
	~Span();

	Span &operator=(const Span &rhs);

	void addNumber(int x);
	void fill();

	int shortestSpan() const;
	int longestSpan() const;

	class SpanFullException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Span full";
		}
	};

	class SpanNotEnoughValuesException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Span not enough values";
		}
	};

private:
	size_t _size;
	std::deque<int> _deque;
};
