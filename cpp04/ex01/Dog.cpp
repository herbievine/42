/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:16:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog"), brain(new Brain())
{
	std::cout << "[Dog] Constructor called" << std::endl;
}

Dog::Dog(const Dog &dog) : Animal(dog), brain(new Brain(*dog.brain))
{
	std::cout << "[Dog] Copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "[Dog] Assignation operator called" << std::endl;

	this->type = rhs.type;
	*brain = *rhs.brain;

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
