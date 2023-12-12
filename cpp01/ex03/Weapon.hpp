/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:39:07 by herbie            #+#    #+#             */
/*   Updated: 2023/12/12 14:05:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon
{
public:
	explicit Weapon(std::string const &type);
	~Weapon();
	std::string const &getType();
	void setType(std::string const &type);

private:
	std::string type;
};

#endif /* WEAPON_HPP */
