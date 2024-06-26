/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/20 08:37:59 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

typedef struct
{
	std::string name;
	int age;
} Data;

class Serializer
{
public:
	static uintptr_t serialize(Data *data);
	static Data *deserialize(uintptr_t raw);

private:
	explicit Serializer();
	Serializer(const Serializer &src);
	~Serializer();

	Serializer &operator=(const Serializer &rhs);
};
