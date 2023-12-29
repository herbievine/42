/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:21:03 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:01:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() : name("Character")
{
	std::cout << "[Character] Constructor called" << std::endl;

	for (int i = 0; i < INVENTORY_SIZE; i++)
		this->inventory[i] = NULL;
}

Character::Character(std::string const &name) : name(name)
{
	std::cout << "[Character] Constructor called" << std::endl;

	for (int i = 0; i < INVENTORY_SIZE; i++)
		this->inventory[i] = NULL;
}

Character::Character(const Character &character)
{
	std::cout << "[Character] Copy constructor called" << std::endl;

	*this = character;
}

Character::~Character()
{
	std::cout << "[Character] Destructor called" << std::endl;

	for (int i = 0; i < INVENTORY_SIZE; i++)
		if (this->inventory[i])
			delete this->inventory[i];
}

Character &Character::operator=(const Character &rhs)
{
	std::cout << "[Character] Assignation operator called" << std::endl;

	this->name = rhs.name;

	for (int i = 0; i < INVENTORY_SIZE; i++)
		if (this->inventory[i])
			delete this->inventory[i];
	for (int i = 0; i < INVENTORY_SIZE; i++)
		if (rhs.inventory[i])
			this->inventory[i] = rhs.inventory[i]->clone();
		else
			this->inventory[i] = NULL;

	return *this;
}

std::string const &Character::getName() const
{
	return this->name;
}

void Character::equip(AMateria *m)
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (!this->inventory[i])
		{
			this->inventory[i] = m;

			std::cout << "[Character] " << this->name << " equiped " << m->getType() << std::endl;

			return;
		}
	}

	std::cout << "[Character] " << this->name << " inventory is full" << std::endl;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= INVENTORY_SIZE)
		return;
	if (this->inventory[idx])
	{
		this->inventory[idx] = NULL;

		std::cout << "[Character] " << this->name << " unequiped " << idx << std::endl;
	}
	else
		std::cout << "[Character] " << this->name << " item " << idx << " is empty" << std::endl;
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= INVENTORY_SIZE)
		return;
	if (this->inventory[idx])
	{
		this->inventory[idx]->use(target);

		std::cout << "[Character] " << this->name << " used " << idx << std::endl;
	}
	else
		std::cout << "[Character] " << this->name << " item " << idx << " is empty" << std::endl;
}
