/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 17:58:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() : type("AMateria")
{
	std::cout << "[AMateria] Constructor called" << std::endl;
}

AMateria::AMateria(std::string const &type) : type(type)
{
	std::cout << "[AMateria] Constructor called" << std::endl;
}

AMateria::AMateria(const AMateria &aMateria)
{
	std::cout << "[AMateria] Copy constructor called" << std::endl;

	*this = aMateria;
}

AMateria::~AMateria()
{
	std::cout << "[AMateria] Destructor called" << std::endl;
}

AMateria &AMateria::operator=(const AMateria &rhs)
{
	std::cout << "[AMateria] Assignation operator called" << std::endl;

	this->type = rhs.type;

	return *this;
}

std::string const &AMateria::getType() const
{
	return this->type;
}
