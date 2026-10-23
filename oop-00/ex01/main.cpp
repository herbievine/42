/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:59:04 by herbie            #+#    #+#             */
/*   Updated: 2026/10/23 11:59:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Graph.hpp"

int main()
{
	Graph graph(Vector2(6, 6));

	graph.addPoint(Vector2(0, 0));
	graph.addPoint(Vector2(2, 2));
	graph.addPoint(Vector2(4, 2));
	graph.addPoint(Vector2(2, 4));
	graph.print();

	std::cout << std::endl;
	graph.addPoint(Vector2(6, 1));
	graph.addPoint(Vector2(-1, 3));
	std::cout << std::endl;

	Graph small(Vector2(3, 2));

	small.addPoint(Vector2(0.4f, 1.2f));
	small.addPoint(Vector2(2, 0));
	small.print();

	return 0;
}
