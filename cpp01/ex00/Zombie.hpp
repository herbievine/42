/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:54:08 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:02:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

class Zombie
{
public:
	explicit Zombie(std::string name);
	~Zombie(void);
	
	void announce(void);

private:
	std::string name;
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif /* ZOMBIE_HPP */