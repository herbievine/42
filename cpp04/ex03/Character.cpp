/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:21:03 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 14:53:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const &name) : name(name)
{
	std::cout << "[Character] Constructor called" << std::endl;
	for (int i = 0; i < INVENTORY_SIZE; i++)
		this->inventory[i] = NULL;
}

Character::~Character()
{
	std::cout << "[Character] Destructor called" << std::endl;
	for (int i = 0; i < INVENTORY_SIZE; i++)
		if (this->inventory[i])
			delete this->inventory[i];
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
