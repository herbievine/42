/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:53:28 by codespace         #+#    #+#             */
/*   Updated: 2024/04/22 13:30:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>

enum e_type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE
};

// bool handleSpecialCases(const std::string &str)
// {
// 	if (!(str.compare("-inff") || str.compare("+inff") || str.compare("nanf") || str.compare("-inf") || str.compare("+inf") || str.compare("nan")))
// 		return false;

// 	// if (str.compare("-inff"))
// 	// {
// 	// }
// }

e_type parseType(const std::string &str, size_t &len)
{

	int i = std::numeric_limits<int>::quiet_NaN();
	double d = std::numeric_limits<double>::quiet_NaN();

	std::cout << i << "|" << d << std::endl;

	size_t dot = str.find('.');
	size_t f = str.find('f');

	if (dot == std::string::npos)
	{
	}

	return FLOAT;
}

void convert(const std::string &str)
{
	size_t len = str.length();
	e_type type = parseType(str, len);
}
