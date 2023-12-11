/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:06:33 by herbie            #+#    #+#             */
/*   Updated: 2023/12/11 15:26:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

#define N 4

int main(void)
{
	Zombie *zombies = zombieHorde(N, "Julien");

	for (int i = 0; i < N; i++)
	{
		zombies[i].announce();
	}

	delete[] zombies;
	return 0;
}