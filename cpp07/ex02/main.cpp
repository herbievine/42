/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/06 14:46:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "array.hpp"

int main()
{
	Array<float> floats(100);
	std::cout << "Size: " << floats.size() << std::endl;

	floats[42] = 4.2f;

	Array<float> copy = floats;

	std::cout << "Original value: " << floats[42] << std::endl;
	std::cout << "Copied value: " << copy[42] << std::endl;

	std::cout << "Original address: " << &floats[42] << std::endl;
	std::cout << "Copied address: " << &copy[42] << std::endl;

	return 0;
}
