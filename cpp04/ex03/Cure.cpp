/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 12:13:31 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
	std::cout << "[Cure] Constructor called" << std::endl;
}

Cure::Cure(const Cure &cure) : AMateria(cure)
{
	std::cout << "[Cure] Copy constructor called" << std::endl;
}

Cure::~Cure()
{
	std::cout << "[Cure] Destructor called" << std::endl;
}

Cure &Cure::operator=(const Cure &rhs)
{
	std::cout << "[Cure] Assignation operator called" << std::endl;

	this->type = rhs.type;

	return *this;
}

AMateria *Cure::clone() const
{
	return new Cure(*this);
}

void Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
