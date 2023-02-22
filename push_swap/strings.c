/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:20:45 by herbie            #+#    #+#             */
/*   Updated: 2023/02/22 08:43:05 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"
#include <stdint.h>

/**
 * @brief The ft_strlen() function computes the length of the string s.
 *
 * @param s
 * @return size_t
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (i[s])
		++i;
	return (i);
}

/**
 * @brief The ft_atoi() function converts the initial portion of the string
 * pointed to by nptr to int representation.
 *
 * @param nptr
 * @return int
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
		if (nptr[i++] == 45)
			sign *= -1;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

/**
 * @brief The ft_calloc() function allocates memory for an array of nmemb
 * elements of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero.
 *
 * @param nmemb
 * @param size
 * @return void*
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	space = malloc(nmemb * size);
	if (!space)
		return (0);
	ft_memset(space, 0, nmemb * size);
	return (space);
}

/**
 * @brief The memset() function writes len bytes of value c (converted to an
 * unsigned char) to the string b.
 *
 * @param s
 * @param c
 * @param n
 * @return void*
 */
void	*ft_memset(void *s, int c, size_t n)
{
	while (n-- > 0)
		((char *)s)[n] = (unsigned char)c;
	return (s);
}

/**
 * @brief The ft_substr() function allocates (with malloc(3)) and returns a
 * substring from the string 's'. The substring begins at index 'start' and is of
 * maximum size 'len'.
 *
 * @param s
 * @param start
 * @param len
 * @return char*
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		str = (char *)ft_calloc(1, sizeof(char));
		if (!str)
			return (0);
		return (str);
	}
	if (ft_strlen(s) < len + start)
		str = (char *)ft_calloc(ft_strlen(s) - start + 1, sizeof(char));
	else
		str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	i = -1;
	while (s[start + ++i] && i < len)
		str[i] = s[start + i];
	return (str);
}
