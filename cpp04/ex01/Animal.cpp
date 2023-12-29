/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:14:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << "[Animal] Constructor called" << std::endl;
}

Animal::Animal(std::string const &type) : type(type)
{
	std::cout << "[Animal] Constructor called" << std::endl;
}

Animal::Animal(const Animal &animal)
{
	std::cout << "[Animal] Copy constructor called" << std::endl;

	*this = animal;
}

Animal::~Animal()
{
	std::cout << "[Animal] Destructor called" << std::endl;
}

Animal &Animal::operator=(const Animal &rhs)
{
	std::cout << "[Animal] Assignation operator called" << std::endl;

	this->type = rhs.type;

	return *this;
}

// cppcheck-suppress unusedFunction
std::string Animal::getType() const
{
	return this->type;
}

// cppcheck-suppress unusedFunction
void Animal::makeSound(void) const
{
	std::cout << "Moo?" << std::endl;
}
