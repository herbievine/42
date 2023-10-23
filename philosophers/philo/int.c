/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:31:42 by codespace         #+#    #+#             */
/*   Updated: 2023/05/21 11:54:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "int.h"
#include <stdbool.h>

/**
 * @brief The ft_atoi funtion converts the initial portion of the string
 * pointed to by str to int representation.
 *
 * @param str
 * @return int
 */
int	ft_atoi(char *str)
{
	int	s;
	int	n;

	s = 1;
	n = 0;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s *= -1;
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - 48;
	return (n * s);
}

/**
 * @brief This function checks if a character is a digit.
 * 
 * @param c
 * @return t_bool 
 */
bool	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/**
 * @brief This function checks if a string is a number.
 * 
 * @param str
 * @return t_bool 
 */
bool	ft_isdigit_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (false);
	return (true);
}
