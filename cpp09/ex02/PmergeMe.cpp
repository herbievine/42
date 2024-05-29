/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/29 14:17:59 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <fstream>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {}

void PmergeMe::operator=(const PmergeMe &rhs) {}

void PmergeMe::merge(std::vector<int> &arr)
{
	int n = arr.size();

	if (n <= 1)
		return;

	std::vector<int> largerElements((n + 1) / 2);
	std::vector<int> smallerElements((n) / 2, 0);

	for (int i = 0; i < n / 2; ++i)
	{
		if (arr[2 * i] > arr[2 * i + 1])
		{
			largerElements[i] = arr[2 * i];
			smallerElements[i] = arr[2 * i + 1];
		}
		else
		{
			largerElements[i] = arr[2 * i + 1];
			smallerElements[i] = arr[2 * i];
		}
	}

	if (n % 2 == 1)
		largerElements[n / 2] = arr[n - 1];

	merge(largerElements);

	std::vector<int> s;

	s.push_back(smallerElements[0]);

	for (int i = 0; i < largerElements.size(); ++i)
		_insert(s, largerElements[i], s.size());

	std::vector<int> remainingSmallerElements(smallerElements.begin() + 1, smallerElements.end());

	static std::uint64_t jacobsthal_nums[63] = {
			2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
			2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
			1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
			178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
			11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
			366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
			11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
			375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
			6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
			96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
			1537228672809129216u, 3074457345618258432u, 6148914691236516864u};

	int idx = 0, smallIndex = 0;
	while (smallIndex < remainingSmallerElements.size() && idx < 63)
	{
		for (int j = 0; j < jacobsthal_nums[idx] && smallIndex < remainingSmallerElements.size(); ++j)
		{
			_insert(s, remainingSmallerElements[smallIndex], s.size());
			++smallIndex;
		}
		++idx;
	}

	for (int i = 0; i < s.size(); ++i)
		arr[i] = s[i];
}

void PmergeMe::merge(std::list<int> &arr)
{
	int n = arr.size();

	if (n <= 1)
		return;

	std::list<int> largerElements;
	std::list<int> smallerElements;

	std::list<int>::iterator it = arr.begin();
	for (int i = 0; i < n / 2; ++i)
	{
		int first = *it++;
		int second = *it++;
		if (first > second)
		{
			largerElements.push_back(first);
			smallerElements.push_back(second);
		}
		else
		{
			largerElements.push_back(second);
			smallerElements.push_back(first);
		}
	}

	if (n % 2 == 1)
		largerElements.push_back(*it);

	merge(largerElements);

	std::list<int> s;
	s.push_back(smallerElements.front());
	smallerElements.pop_front();

	for (std::list<int>::iterator el = largerElements.begin(); el != largerElements.end(); ++el)
		_insert(s, *el);

	std::vector<int> remainingSmallerElements(smallerElements.begin(), smallerElements.end());

	static const unsigned long long jacobsthal_nums[63] = {
			2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
			2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
			1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
			178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
			11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
			366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
			11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
			375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
			6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
			96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
			1537228672809129216u, 3074457345618258432u, 6148914691236516864u};

	int idx = 0, smallIndex = 0;
	while (smallIndex < remainingSmallerElements.size() && idx < 63)
	{
		for (int j = 0; j < jacobsthal_nums[idx] && smallIndex < remainingSmallerElements.size(); ++j)
		{
			_insert(s, remainingSmallerElements[smallIndex]);
			++smallIndex;
		}
		++idx;
	}

	arr = s;
}

void PmergeMe::_insert(std::vector<int> &arr, int value, int h)
{
	int l = 0;

	while (l < h)
	{
		int m = l + (h - l) / 2;

		if (arr[m] < value)
			l = m + 1;
		else
			h = m;
	}

	arr.insert(arr.begin() + l, value);
}

void PmergeMe::_insert(std::list<int> &arr, int value)
{
	std::list<int>::iterator it = arr.begin();
	std::list<int>::iterator end = arr.end();
	while (it != end && *it < value)
	{
		++it;
	}
	arr.insert(it, value);
}
