/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:44:54 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 13:19:06 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

ClapTrap::ClapTrap(const std::string &name) : name(name), hitPoints(10), energyPoints(10), attackDamage(1)
{
	std::cout << "[ClapTrap] Constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "[ClapTrap] Destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &name)
{
	std::cout << "[ClapTrap] " << this->name << " attacks " << name << ", causing " << this->attackDamage << " point(s) of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "[ClapTrap] " << this->name << " takes " << amount << " point(s) of damage!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "[ClapTrap] " << this->name << " repairs " << amount << " hitpoint(s)!" << std::endl;
}
