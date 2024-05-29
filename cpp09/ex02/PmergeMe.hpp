/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/29 14:17:41 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <list>

class PmergeMe
{
private:
	PmergeMe();
	~PmergeMe();
	PmergeMe(const PmergeMe &src);

	void operator=(const PmergeMe &rhs);

	static void _insert(std::vector<int> &vec, int value, int end);
	static void _insert(std::list<int> &arr, int value);

public:
	static void merge(std::vector<int> &arr);
	static void merge(std::list<int> &arr);
};
