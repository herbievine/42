/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/06 14:46:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

int main()
{
	int nums[5] = {1, 2, 42, 69, 420};
	iter(nums, 5, print<const int>);

	std::string strs[3] = {"hello", "world", "!"};
	iter(strs, 3, print<const std::string>);

	return 0;
}
