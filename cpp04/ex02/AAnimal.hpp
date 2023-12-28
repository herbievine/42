/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:49:17 by herbie            #+#    #+#             */
/*   Updated: 2023/12/28 17:27:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>

class AAnimal
{
public:
	AAnimal();
	explicit AAnimal(std::string const &type);
	AAnimal(const AAnimal &aanimal);
	virtual ~AAnimal();

	AAnimal &operator=(const AAnimal &aanimal);

	std::string getType() const;
	virtual void makeSound() const = 0;

protected:
	std::string type;
};

#endif /* AANIMAL_HPP */
