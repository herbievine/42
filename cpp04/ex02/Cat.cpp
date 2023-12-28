/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 17:57:27 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : AAnimal("Cat"), brain(new Brain())
{
	std::cout << "[Cat] Constructor called" << std::endl;
}

Cat::Cat(const Cat &cat) : AAnimal(cat), brain(new Brain(*cat.brain))
{
	std::cout << "[Cat] Copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &rhs)
{
	this->type = rhs.type;
	*brain = *rhs.brain;

	return (*this);
}

Cat::~Cat()
{
	delete this->brain;

	std::cout << "[Cat] Destructor called" << std::endl;
}

// cppcheck-suppress unusedFunction
void Cat::makeSound(void) const
{
	std::cout << "Meow!" << std::endl;
}
