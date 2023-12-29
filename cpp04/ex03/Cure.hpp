/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:01:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

class Cure : public AMateria
{
public:
	Cure();
	Cure(const Cure &cure);
	~Cure();

	Cure &operator=(const Cure &rhs);

	// cppcheck-suppress missingOverride
	AMateria *clone() const;
	// cppcheck-suppress missingOverride
	void use(ICharacter &target);
};

#endif /* CURE_HPP */
