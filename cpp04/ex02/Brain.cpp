/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:53:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:16:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() : ideas()
{
	std::cout << "[Brain] Constructor called" << std::endl;
}

Brain::Brain(const Brain &brain)
{
	std::cout << "[Brain] Copy constructor called" << std::endl;

	*this = brain;
}

Brain::~Brain()
{
	std::cout << "[Brain] Destructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &rhs)
{
	std::cout << "[Brain] Assignation operator called" << std::endl;

	for (int i = 0; i < 100; i++)
		this->ideas[i] = rhs.ideas[i];

	return *this;
}
