/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 15:15:27 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal("Dog"), brain(new Brain())
{
	std::cout << "[Dog] Constructor called" << std::endl;
}

Dog::Dog(const Dog &rhs) : Animal(rhs), brain(new Brain(*rhs.brain))
{
	std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &rhs)
{
	if (this != &rhs)
	{
		this->type = rhs.type;
		*brain = *rhs.brain;
	}
	return (*this);
}

Dog::~Dog()
{
	delete this->brain;

	std::cout << "[Dog] Destructor called" << std::endl;
}

void Dog::makeSound(void) const
{
	std::cout << "Woof!" << std::endl;
}
