/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector2.hpp"

Vector2::Vector2(float x, float y) : _x(x), _y(y)
{
}

Vector2::Vector2(const Vector2 &src)
{
	*this = src;
}

Vector2::~Vector2()
{
}

Vector2 &Vector2::operator=(const Vector2 &rhs)
{
	if (&rhs != this)
	{
		this->_x = rhs._x;
		this->_y = rhs._y;
	}

	return *this;
}

const float &Vector2::getX() const
{
	return this->_x;
}

const float &Vector2::getY() const
{
	return this->_y;
}
