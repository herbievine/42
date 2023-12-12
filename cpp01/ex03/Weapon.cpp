/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:39:04 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:05:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string const &type)
{
	this->type = type;
}

Weapon::~Weapon()
{
}

std::string const &Weapon::getType()
{
	return this->type;
}

void Weapon::setType(std::string const &type)
{
	this->type = type;
}