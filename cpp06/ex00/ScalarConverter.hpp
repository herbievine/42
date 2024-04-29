/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/04/22 13:31:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class ScalarConverter
{
public:
	static void convert(const std::string &str);

private:
	explicit ScalarConverter();
	ScalarConverter(const ScalarConverter &src);
	~ScalarConverter();

	ScalarConverter &operator=(const ScalarConverter &rhs);
};

void convert(const std::string &str);
