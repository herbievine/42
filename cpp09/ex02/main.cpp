/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/29 14:19:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <time.h>
#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <array of positive ints>" << std::endl;
		return 1;
	}

	std::vector<int> vector;
	std::list<int> list;

	for (int i = 1; i < argc; i++)
	{
		int n = std::atoi(argv[i]);

		if (n < 0)
		{
			std::cerr << "Error" << std::endl;
			return 1;
		}

		vector.push_back(n);
		list.push_back(n);
	}

	std::cout << "Before: ";
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	const clock_t beginTimeVector = clock();
	PmergeMe::merge(vector);
	const clock_t diffTimeVector = static_cast<double>(clock() - beginTimeVector) / CLOCKS_PER_SEC * 1000000;

	const clock_t beginTimeList = clock();
	PmergeMe::merge(list);
	const clock_t diffTimeList = static_cast<double>(clock() - beginTimeList) / CLOCKS_PER_SEC * 1000000;

	std::cout << "After: ";
	std::copy(vector.begin(), vector.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector container: " << diffTimeVector << " us" << std::endl;
	std::cout << "Time to process a range of " << list.size() << " elements with std::list container: " << diffTimeList << " us" << std::endl;
}
