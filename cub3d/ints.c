/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:31:42 by codespace         #+#    #+#             */
/*   Updated: 2024/03/15 17:02:51 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ints.h"
#include "str.h"
#include "mem.h"

/**
 * @brief The ft_intlen funtion returns the number of digits in the integer
 * received as an argument.
 * 
 * @param n 
 * @return int 
 */
int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * @brief The ft_itoa funtion allocates (with malloc(3)) and returns a
 * string representing the integer received as an argument.
 * 
 * @param n 
 * @return char* 
 */
char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_substr("-2147483648", 0, 11));
	if (n == 0)
		return (ft_substr("0", 0, 1));
	len = ft_intlen(n);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (len-- && n)
	{
		str[len] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

/**
 * @brief The ft_atoi function converts the initial portion of the string
 * pointed to by str to int representation.
 * 
 * @param str 
 * @return int 
 */
int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i++] - '0');
		if (n < 0 && sign == 1)
			return (-1);
		if (n < 0 && sign == -1)
			return (0);
	}
	return (n * sign);
}
