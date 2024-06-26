/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:23 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 15:06:53 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"
#include <iostream>

int main(void)
{
	IMateriaSource *src = new MateriaSource();

	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("me");

	AMateria *tmp, *cure;
	tmp = src->createMateria("ice");
	me->equip(tmp);

	tmp = src->createMateria("cure");
	me->equip(tmp);

	tmp = src->createMateria("ice");
	me->equip(tmp);

	cure = src->createMateria("cure");
	me->equip(cure);

	tmp = src->createMateria("unknown");
	me->equip(tmp);

	ICharacter *bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);
	me->use(2, *bob);
	me->use(3, *bob);

	me->unequip(3);
	me->use(3, *bob);

	// We need to delete the 3rd item as the
	// unequip function doesn't do it for us
	delete cure;

	delete bob;
	delete me;
	delete src;

	return 0;
}
