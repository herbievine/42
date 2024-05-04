/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:22:29 by codespace         #+#    #+#             */
/*   Updated: 2024/05/04 09:52:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

int main()
{
	Data data = {"John", 42};

	uintptr_t raw = Serializer::serialize(&data);

	std::cout << "Raw: " << raw << std::endl;

	const Data *data2 = Serializer::deserialize(raw);

	std::cout << "Name: " << data2->name << std::endl;
	std::cout << "Age: " << data2->age << std::endl;

	return 0;
}
