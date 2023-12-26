/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:22:57 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 13:33:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(const std::string &name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;

	std::cout << "[FragTrap] Constructor called" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "[FragTrap] Destructor called" << std::endl;
}

void FragTrap::highFivesGuys()
{
	std::cout << "[FragTrap] " << this->name << " has requested a high five!" << std::endl;
}
