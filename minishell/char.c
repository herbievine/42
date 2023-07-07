/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:58:37 by herbie            #+#    #+#             */
/*   Updated: 2023/07/07 13:58:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"

/**
 * @brief The ft_isascii funtion tests for an ASCII character, which is any
 * character between 0 and octal 0177 inclusive.
 * 
 * @param c 
 * @return int 
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/**
 * @brief The ft_isdigit funtion tests for a decimal digit character.
 * Regardless of locale, this includes the following characters only: '0' '1'
 * '2' '3' '4' '5' '6' '7' '8' '9'.
 * 
 * @param c 
 * @return int 
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/**
 * @brief The ft_isalpha funtion tests for any character for which isupper(3)
 * or islower(3) is true. The value of the argument must be representable as an
 * unsigned char or the value of EOF.
 * 
 * @param c 
 * @return int 
 */
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/**
 * @brief The ft_isalnum funtion returns zero if the character tests false and
 * returns non-zero if the character tests true.
 * 
 * @param c 
 * @return int 
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/**
 * @brief The ft_isspace funtion tests for the white-space characters. For any
 * locale, this returns true for the following characters only: space ('\ '),
 * newline ('\n'), and horizontal tab ('\t').
 * 
 * @param c 
 * @return int 
 */
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
