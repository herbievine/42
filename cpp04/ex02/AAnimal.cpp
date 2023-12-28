/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:17:02 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("AAnimal")
{
	std::cout << "[AAnimal] Constructor called" << std::endl;
}

AAnimal::AAnimal(std::string const &type) : type(type)
{
	std::cout << "[AAnimal] Constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &aanimal)
{
	std::cout << "[AAnimal] Copy constructor called" << std::endl;

	*this = aanimal;
}

AAnimal::~AAnimal()
{
	std::cout << "[AAnimal] Destructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &aanimal)
{
	std::cout << "[AAnimal] Assignation operator called" << std::endl;

	this->type = aanimal.type;

	return *this;
}

// cppcheck-suppress unusedFunction
std::string AAnimal::getType() const
{
	return this->type;
}
