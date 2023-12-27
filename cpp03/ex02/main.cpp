/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:58:21 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 13:34:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <iostream>

int main(void)
{
	FragTrap frag("James Bond");

	frag.attack("Jennifer Aniston");
	frag.takeDamage(76);
	frag.beRepaired(34);
	frag.attack("Jennifer Aniston");
	frag.highFivesGuys();

	return 0;
}
