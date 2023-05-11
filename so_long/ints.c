/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:31:42 by codespace         #+#    #+#             */
/*   Updated: 2023/05/11 17:31:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ints.h"
#include "str.h"
#include "mem.h"

/**
 * @brief The ft_intlen() function returns the number of digits in the integer
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
 * @brief The ft_itoa() function allocates (with malloc(3)) and returns a
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
