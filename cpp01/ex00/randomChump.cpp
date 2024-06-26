/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:03:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:02:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <iostream>

// cppcheck-suppress passedByValue
void randomChump(std::string name)
{
	Zombie *zombie = newZombie(name);
	zombie->announce();
	delete zombie;
}
