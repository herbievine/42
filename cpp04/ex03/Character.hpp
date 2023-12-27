/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 15:21:44 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <iostream>

#define INVENTORY_SIZE 4

class Character : public ICharacter
{
public:
	explicit Character(std::string const &name);
	virtual ~Character();

	// cppcheck-suppress missingOverride
	std::string const &getName() const;
	// cppcheck-suppress missingOverride
	void equip(AMateria *m);
	// cppcheck-suppress missingOverride
	void unequip(int idx);
	// cppcheck-suppress missingOverride
	void use(int idx, ICharacter &target);

private:
	std::string name;
	AMateria *inventory[INVENTORY_SIZE];
};

#endif /* CHARACTER_HPP */
