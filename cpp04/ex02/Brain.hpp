/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/26 17:57:02 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

#define BRAIN_IDEAS 100

class Brain
{
public:
	Brain();
	Brain(const Brain &brain);
	~Brain();

	Brain &operator=(const Brain &rhs);

private:
	std::string *ideas[BRAIN_IDEAS];
};

#endif /* BRAIN_HPP */
