/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:35:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 14:54:57 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	std::cout << "[MateriaSource] Constructor called" << std::endl;
	for (int i = 0; i < MAX_MATERIA; i++)
		this->materia[i] = NULL;
}

MateriaSource::~MateriaSource()
{
	std::cout << "[MateriaSource] Destructor called" << std::endl;
	for (int i = 0; i < MAX_MATERIA; i++)
		if (this->materia[i])
			delete this->materia[i];
}

void MateriaSource::learnMateria(AMateria *m)
{
	for (int i = 0; i < MAX_MATERIA; i++)
	{
		if (!this->materia[i])
		{
			this->materia[i] = m;

			std::cout << "[MateriaSource] " << m->getType() << " learned" << std::endl;

			return;
		}
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < MAX_MATERIA; i++)
	{
		if (this->materia[i] && this->materia[i]->getType() == type)
		{
			std::cout << "[MateriaSource] " << type << " created" << std::endl;

			return this->materia[i]->clone();
		}
	}
	return NULL;
}
