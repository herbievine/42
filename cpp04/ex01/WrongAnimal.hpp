/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 17:48:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
#define WRONG_ANIMAL_HPP

#include <iostream>

class WrongAnimal
{
public:
	WrongAnimal();
	explicit WrongAnimal(std::string const &type);
	WrongAnimal(const WrongAnimal &wrongAnimal);
	virtual ~WrongAnimal();

	WrongAnimal &operator=(const WrongAnimal &rhs);

	std::string getType() const;
	virtual void makeSound(void) const;

protected:
	std::string type;
};

#endif /* WRONG_ANIMAL_HPP */
