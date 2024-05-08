/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:36 by codespace         #+#    #+#             */
/*   Updated: 2024/05/08 08:14:46 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <limits>

std::string ScalarConverter::str;
t_type ScalarConverter::type;

void ScalarConverter::convert(const std::string &str)
{
	if (str.length() == 0)
		throw SC::InvalidScalarException();

	SC::str = str;
	SC::setType(str);

	switch (SC::type)
	{
	case CHAR:
		SC::printChar();
		break;
	case NUMBER:
		SC::printNumber();
		break;
	case SPECIAL:
		SC::printSpecial();
		break;
	case INVALID:
		throw SC::InvalidScalarException();
		break;
	}
}

/**
 * @brief The setType function parses the string and sets the type of the scalar.
 * It has to consider the following cases:
 *
 * - If the string is a single character, it is a char.
 * - If the string is a number, check whether it's an int, float, or double.
 * - If the string may contain values such as -inf, +inf, or nan, it is a special case.
 * - If the string is anything else, it is an invalid case.
 *
 * @param str
 */
void ScalarConverter::setType(const std::string &str)
{
	if (SC::isChar())
		SC::type = CHAR;
	else if (SC::isNumber())
		SC::type = NUMBER;
	else if (SC::isSpecial())
		SC::type = SPECIAL;
	else
		SC::type = INVALID;
}

bool ScalarConverter::isChar()
{
	return SC::str.length() == 1 && !std::isdigit(SC::str[0]);
}

/**
 * @brief The isNumber function checks if the string is a number. It has to consider the following cases:
 *
 * - The string may start with a '+' or '-' sign.
 * - The string may contain a single '.' character.
 * - The string may contain only digits, a single '.' character, and a single 'f' character at the end.
 * - Both "42.f" and "42." are valid cases.
 *
 * @return bool
 */
bool ScalarConverter::isNumber()
{
	size_t i = (SC::str[0] == '-' || SC::str[0] == '+') ? 1 : 0;
	bool dotSeen = false;

	if (!std::isdigit(SC::str[i]) && SC::str[i] != '.')
		return false;
	while (i < SC::str.length())
	{
		if (SC::str[i] == '.')
		{
			if (dotSeen)
				return false;
			dotSeen = true;
		}
		else if (!std::isdigit(SC::str[i]))
			break;
		i++;
	}
	if (str[i] == 'f' && (std::isdigit(SC::str[i - 1]) || SC::str[i - 1] == '.'))
		i++;
	return i == SC::str.length();
}

bool ScalarConverter::isSpecial()
{
	return (
			SC::str.compare("-inff") == 0 ||
			SC::str.compare("+inff") == 0 ||
			SC::str.compare("nanf") == 0 ||
			SC::str.compare("-inf") == 0 ||
			SC::str.compare("+inf") == 0 ||
			SC::str.compare("nan") == 0);
}

/**
 * @brief The printChar function prints the char. If the char is printable, it prints the char,
 * otherwise, it prints "non displayable". It also prints the int, float, and double values.
 */
void ScalarConverter::printChar()
{
	double value = 0;

	value = double(str[0]);
	if (isprint(str[0]))
		std::cout << "char: " << str[0] << std::endl;
	else
		std::cout << "char: non displayable" << std::endl;
	std::cout << "int: " << static_cast<int>(value) << std::endl;
	std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << std::endl;
}

/**
 * @brief The printNumber function prints the number. In case of overflow,it prints "impossible",
 * otherwise, it prints the number in char, int, float, and double.
 */
void ScalarConverter::printNumber()
{
	double value = 0;

	try
	{
		value = std::stod(SC::str);
	}
	catch (const std::out_of_range &e)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	if (value > std::numeric_limits<char>::max() || value < std::numeric_limits<char>::min())
		std::cout << "char: impossible" << std::endl;
	else if (isprint(static_cast<char>(value)))
		std::cout << "char: " << static_cast<char>(value) << std::endl;
	else
		std::cout << "char: non displayable" << std::endl;
	if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	if (value > std::numeric_limits<float>::max() || value < -std::numeric_limits<float>::max())
		std::cout << "float: impossible" << std::endl;
	else
		std::cout << "float: " << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(value) << std::endl;
}

/**
 * @brief The printSpecial function prints the special cases.
 */
void ScalarConverter::printSpecial()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (str == "nan" || str == "nanf")
	{
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (str == "+inf" || str == "+inff")
	{
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (str == "-inf" || str == "-inff")
	{
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
}
