/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/07 11:01:31 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() {}

Span::Span(unsigned int n)
{
	_size = n;
}

Span::Span(const Span &src) : _deque(src._deque)
{
	_size = src._size;
}

Span::~Span() {}

Span &Span::operator=(const Span &rhs)
{
	if (&rhs != this)
	{
		_size = rhs._size;
		_deque = rhs._deque;
	}

	return *this;
}

void Span::addNumber(int x)
{
	if (_deque.size() == _size)
		throw SpanFullException();

	_deque.push_back(x);
}

void Span::fill()
{
	if (_deque.size() == _size)
		throw SpanFullException();

	while (_deque.size() < _size)
		_deque.push_back(rand());
}

int Span::shortestSpan() const
{
	if (_deque.size() < 2)
		throw SpanNotEnoughValuesException();

	std::deque<int> copy(_deque);
	std::sort(copy.begin(), copy.end(), std::less<int>());
	std::deque<int> diff(copy);
	std::adjacent_difference(copy.begin(), copy.end(), diff.begin());
	
	return *std::min_element(diff.begin(), diff.end()); 
}

int Span::longestSpan() const
{
	if (_deque.size() < 2)
		throw SpanNotEnoughValuesException();

	std::deque<int> copy(_deque);
	std::sort(copy.begin(), copy.end());

	return copy[copy.size() - 1] - copy[0];
}
