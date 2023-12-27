/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 18:15:31 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : type("Animal")
{
	std::cout << "[Animal] Constructor called" << std::endl;
}

Animal::Animal(std::string const &type) : type(type)
{
	std::cout << "[Animal] Constructor called" << std::endl;
}

Animal::~Animal()
{
	std::cout << "[Animal] Destructor called" << std::endl;
}

std::string Animal::getType() const
{
	return this->type;
}

void Animal::makeSound(void) const
{
	std::cout << "Moo?" << std::endl;
}
