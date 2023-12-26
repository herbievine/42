/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:19:36 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 13:55:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
public:
	explicit ScavTrap(const std::string &name);
	~ScavTrap();

	// cppcheck-suppress missingOverride
	void attack(const std::string &target);
	void guardGate();
};

#endif /* SCAVTRAP_HPP */