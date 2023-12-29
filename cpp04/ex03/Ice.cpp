/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:02:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
	std::cout << "[Ice] Constructor called" << std::endl;
}

Ice::Ice(const Ice &ice) : AMateria(ice)
{
	std::cout << "[Ice] Copy constructor called" << std::endl;
}

Ice::~Ice()
{
	std::cout << "[Ice] Destructor called" << std::endl;
}

Ice &Ice::operator=(const Ice &rhs)
{
	std::cout << "[Ice] Assignation operator called" << std::endl;

	this->type = rhs.type;

	return *this;
}

AMateria *Ice::clone() const
{
	return new Ice(*this);
}

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
