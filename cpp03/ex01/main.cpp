/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:58:21 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 13:27:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

int main(void)
{
	ScavTrap scav("Sponge Bob");

	scav.attack("42 staff");
	scav.takeDamage(2);
	scav.beRepaired(1);
	scav.attack("more 42 staff");
	scav.guardGate();

	return 0;
}