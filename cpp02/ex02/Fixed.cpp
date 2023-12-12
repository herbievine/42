/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:44:54 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:20:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : fixedPointValue(0)
{
}

Fixed::Fixed(const int n) : fixedPointValue(n << this->fractionalBits)
{
}

Fixed::Fixed(const float n) : fixedPointValue(std::roundf(n * (1 << this->fractionalBits)))
{
}

Fixed::Fixed(const Fixed &rhs)
{
	this->setRawBits(rhs.getRawBits());
}

Fixed::~Fixed()
{
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	this->setRawBits(rhs.getRawBits());
	return *this;
}

bool Fixed::operator>(const Fixed &rhs) const
{
	return this->getRawBits() > rhs.getRawBits();
}

bool Fixed::operator<(const Fixed &rhs) const
{
	return this->getRawBits() < rhs.getRawBits();
}

bool Fixed::operator>=(const Fixed &rhs) const
{
	return this->getRawBits() >= rhs.getRawBits();
}

bool Fixed::operator<=(const Fixed &rhs) const
{
	return this->getRawBits() <= rhs.getRawBits();
}

bool Fixed::operator==(const Fixed &rhs) const
{
	return this->getRawBits() == rhs.getRawBits();
}

bool Fixed::operator!=(const Fixed &rhs) const
{
	return this->getRawBits() != rhs.getRawBits();
}

Fixed Fixed::operator+(const Fixed &rhs) const
{
	return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed &rhs) const
{
	return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed &rhs) const
{
	return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed &rhs) const
{
	if (rhs.getRawBits() == 0)
		throw std::runtime_error("Division by zero");

	return Fixed(this->toFloat() / rhs.toFloat());
}

// Prefix
Fixed &Fixed::operator++(void)
{
	this->fixedPointValue++;
	return *this;
}

Fixed &Fixed::operator--(void)
{
	this->fixedPointValue--;
	return *this;
}

// Postfix
Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	operator++();
	return tmp;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	operator--();
	return tmp;
}

// cppcheck-suppress unusedFunction
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

int Fixed::getRawBits(void) const
{
	return this->fixedPointValue;
}

void Fixed::setRawBits(int const raw)
{
	this->fixedPointValue = raw;
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(this->getRawBits()) / (1 << this->fractionalBits);
}

// cppcheck-suppress unusedFunction
int Fixed::toInt(void) const
{
	return this->getRawBits() >> this->fractionalBits;
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
	o << i.toFloat();
	return o;
}
