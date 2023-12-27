/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:33:28 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 15:23:25 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIA_SOURCE_HPP
#define MATERIA_SOURCE_HPP

#include "IMateriaSource.hpp"
#include <iostream>

#define MAX_MATERIA 4

class MateriaSource : public IMateriaSource
{
public:
	MateriaSource();
	~MateriaSource();

	// cppcheck-suppress missingOverride
	void learnMateria(AMateria *);
	// cppcheck-suppress missingOverride
	AMateria *createMateria(std::string const &type);

private:
	AMateria *materia[MAX_MATERIA];
};

#endif /* MATERIA_SOURCE_HPP */
