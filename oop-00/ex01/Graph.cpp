/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Graph.hpp"

static const float MAX_SIZE = 100;

// Written so that NaN fails too (every comparison with NaN is false).
static bool isValidSize(float v)
{
	return v >= 1 && v <= MAX_SIZE;
}

static Vector2 checkedSize(const Vector2 &size)
{
	if (isValidSize(size.getX()) && isValidSize(size.getY()))
		return Vector2(std::floor(size.getX()), std::floor(size.getY()));

	std::cerr << "Graph: invalid size, using 0x0" << std::endl;

	return Vector2(0, 0);
}

static int cell(float v)
{
	return static_cast<int>(std::floor(v + 0.5f));
}

static int digits(int n)
{
	std::ostringstream oss;

	oss << n;

	return oss.str().size();
}

Graph::Graph(const Vector2 &size) : _size(checkedSize(size))
{
}

Graph::Graph(const Graph &src) : _size(src._size)
{
	*this = src;
}

Graph::~Graph()
{
}

Graph &Graph::operator=(const Graph &rhs)
{
	if (&rhs != this)
	{
		this->_size = rhs._size;
		this->_points = rhs._points;
	}

	return *this;
}

/**
 * @brief Adds a point to the graph if it fits inside the size. The check is
 * done on the float values before any conversion to int, so huge values or
 * NaN cannot overflow.
 *
 * @param point
 * @return true if the point was added
 */
bool Graph::addPoint(const Vector2 &point)
{
	const float &x = point.getX();
	const float &y = point.getY();

	if (!(x >= 0 && y >= 0 && std::floor(x + 0.5f) <= this->_size.getX() - 1 && std::floor(y + 0.5f) <= this->_size.getY() - 1))
	{
		std::cerr << "Graph: point " << x << "/" << y << " rejected (outside the graph)" << std::endl;
		return false;
	}

	this->_points.push_back(point);

	return true;
}

/**
 * @brief Prints the graph on the console, rows from the top (y max) down to 0,
 * each prefixed by its y label, then the x axis labels. Labels are padded so
 * columns stay aligned with two-digit coordinates.
 */
void Graph::print() const
{
	const int width = static_cast<int>(this->_size.getX());
	const int height = static_cast<int>(this->_size.getY());

	if (width == 0 || height == 0)
		return;

	const int yw = digits(height - 1);
	const int xw = digits(width - 1);

	for (int y = height - 1; y >= 0; --y)
	{
		std::cout << std::setw(yw) << y;
		for (int x = 0; x < width; ++x)
		{
			char c = '.';

			for (std::vector<Vector2>::const_iterator it = this->_points.begin(); it != this->_points.end(); ++it)
				if (cell(it->getX()) == x && cell(it->getY()) == y)
					c = 'X';
			std::cout << ' ' << std::setw(xw) << c;
		}
		std::cout << std::endl;
	}
	std::cout << std::setw(yw) << ' ';
	for (int x = 0; x < width; ++x)
		std::cout << ' ' << std::setw(xw) << x;
	std::cout << std::endl;
}
