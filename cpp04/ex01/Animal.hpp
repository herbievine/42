/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 18:03:13 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
public:
	Animal();
	explicit Animal(std::string const &type);
	Animal(const Animal &animal);
	virtual ~Animal();

	Animal &operator=(const Animal &rhs);

	std::string getType() const;
	virtual void makeSound() const;

protected:
	std::string type;
};

#endif /* ANIMAL_HPP */
