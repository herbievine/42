/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:19:36 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 16:24:17 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
public:
	FragTrap();
	explicit FragTrap(const std::string &name);
	FragTrap(const FragTrap &fragTrap);
	~FragTrap();

	FragTrap &operator=(const FragTrap &fragTrap);

	void highFivesGuys(void);
};

#endif /* FRAGTRAP_HPP */
