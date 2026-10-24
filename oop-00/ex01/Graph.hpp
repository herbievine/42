/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include "Vector2.hpp"

// size is the number of cells per axis: Graph(Vector2(6, 6)) shows coordinates
// 0..5. A float coordinate is drawn in the cell of its nearest integer.
// _size and _points are private: the only way in is addPoint(), which rejects
// invalid points, and the only way out is print(), so the graph is always
// drawable.
class Graph
{
public:
	// An invalid size (< 1, > 100, NaN) is replaced by 0x0 and reported on stderr.
	explicit Graph(const Vector2 &size);
	Graph(const Graph &src);
	~Graph();

	Graph &operator=(const Graph &rhs);

	// Returns false and prints a message if the point is negative or out of
	// the size.
	bool addPoint(const Vector2 &point);
	void print() const;

private:
	Vector2 _size;
	std::vector<Vector2> _points;
};

#endif /* GRAPH_HPP */
