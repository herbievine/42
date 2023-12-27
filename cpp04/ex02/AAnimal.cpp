/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 15:20:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal(void) : type("AAnimal")
{
	std::cout << "[AAnimal] Constructor called" << std::endl;
}

AAnimal::AAnimal(std::string const &type) : type(type)
{
	std::cout << "[AAnimal] Constructor called" << std::endl;
}

AAnimal::~AAnimal()
{
	std::cout << "[AAnimal] Destructor called" << std::endl;
}

// cppcheck-suppress unusedFunction
std::string AAnimal::getType() const
{
	return this->type;
}

// cppcheck-suppress unusedFunction
void AAnimal::makeSound(void) const
{
	std::cout << "Moo?" << std::endl;
}
