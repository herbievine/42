/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:22:57 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 16:23:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("ScavTrap")
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;

	std::cout << "[ScavTrap] Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;

	std::cout << "[ScavTrap] Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &scavTrap)
{
	std::cout << "[ScavTrap] Copy constructor called" << std::endl;
	*this = scavTrap;
}

ScavTrap::~ScavTrap()
{
	std::cout << "[ScavTrap] Destructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &scavTrap)
{
	std::cout << "[ScavTrap] Assignation operator called" << std::endl;
	this->name = scavTrap.name;
	this->hitPoints = scavTrap.hitPoints;
	this->energyPoints = scavTrap.energyPoints;
	this->attackDamage = scavTrap.attackDamage;
	return *this;
}

void ScavTrap::attack(const std::string &name)
{
	std::cout << "[ScavTrap] " << this->name << " attacks " << name << ", causing " << this->attackDamage << " point(s) of damage!" << std::endl;
}

// cppcheck-suppress unusedFunction
void ScavTrap::guardGate()
{
	std::cout << "[ScavTrap] " << this->name << " has enterred in Gate keeper mode." << std::endl;
}
