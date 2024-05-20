/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:08:39 by codespace         #+#    #+#             */
/*   Updated: 2024/05/20 08:23:59 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

typedef enum e_type
{
	CHAR,
	NUMBER,
	SPECIAL,
	INVALID
} t_type;

class ScalarConverter
{
public:
	typedef ScalarConverter SC;

	static void convert(const std::string &str);

	class InvalidScalarException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Invalid scalar";
		}
	};

private:
	explicit ScalarConverter();
	ScalarConverter(const ScalarConverter &src);
	~ScalarConverter();

	ScalarConverter &operator=(const ScalarConverter &rhs);

	static std::string str;
	static t_type type;

	static bool isChar();
	static bool isNumber();
	static bool isSpecial();

	static void setType(const std::string &str);

	static void printChar();
	static void printNumber();
	static void printSpecial();
};
