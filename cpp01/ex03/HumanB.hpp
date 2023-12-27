/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:39:00 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:06:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_B_HPP
#define HUMAN_B_HPP

#include "Weapon.hpp"
#include <iostream>

class HumanB
{
public:
	explicit HumanB(std::string const &name);
	~HumanB();
	
	void attack();
	void setWeapon(Weapon &weapon);

private:
	std::string name;
	Weapon *weapon;
};

#endif /* HUMAN_B_HPP */
