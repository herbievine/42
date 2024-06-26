/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:14:34 by herbie            #+#    #+#             */
/*   Updated: 2023/12/27 14:33:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// cppcheck-suppress passedByValue
Zombie *zombieHorde(int N, std::string name)
{
	int i;

	Zombie *zombie = new Zombie[N];
	for (i = 0; i < N; i++)
		zombie[i].setName(name);

	return (zombie);
}
