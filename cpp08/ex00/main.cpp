/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/29 14:29:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iterator>
#include "easyfind.hpp"

template <typename T>
void find(T &data, int value)
{
	const int *val = easyfind(data, value);

	if (val)
		std::cout << "found (" << *val << ")" << std::endl;
	else
		std::cout << "not found" << std::endl;
}

int main()
{
	int nums[8] = {9, 4, 7, 6, 1, 5, 8, 3};
	int value = 1;

	std::cout << "Vector: ";
	std::vector<int> vector(nums, nums + 8);
	find(vector, value);

	std::cout << "List: ";
	std::list<int> list(nums, nums + 8);
	find(list, value);

	std::cout << "Deque: ";
	std::deque<int> deque(nums, nums + 8);
	find(deque, value);

	return 0;
}
