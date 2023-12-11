/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 15:09:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
	Zombie *zombie1 = newZombie("Zombie1");
	Zombie *zombie2 = newZombie("Zombie2");

	zombie1->announce();
	zombie2->announce();
	delete zombie1;
	delete zombie2;
	randomChump("NewZombie1");
	randomChump("NewZombie2");
	return 0;
}