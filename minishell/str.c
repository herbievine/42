/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:14:22 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "mem.h"
#include <stdlib.h>

/**
 * @brief The ft_strlen funtion computes the length of the string s.
 *
 * @param s
 * @return size_t
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief The ft_strchr funtion locates the first occurrence of c (converted
 * to a char) in the string pointed to by s. The terminating null character is
 * considered to be part of the string; therefore if c is '\0', the functions
 * locate the terminating '\0'.
 *
 * @param s
 * @param c
 * @return char*
 */
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	if (!c)
		return ((char *)(s + ft_strlen(s)));
	while (++i < ft_strlen(s))
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (NULL);
}

/**
 * @brief The ft_strjoin funtion allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation of 's1' and 's2'.
 *
 * @param s1
 * @param s2
 * @return char*
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dup;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	dup = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup[ft_strlen(s1) + ft_strlen(s2)] = 0;
	i = 0;
	while (*s1)
		dup[i++] = *s1++;
	while (*s2)
		dup[i++] = *s2++;
	return (dup);
}

/**
 * @brief The ft_strncmp funtion lexicographically compares the
 * null-terminated strings s1 and s2.
 *
 * @param s1
 * @param s2
 * @param n
 * @return int
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/**
 * @brief The ft_substr funtion allocates (with malloc(3)) and returns a
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
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_calloc(1, sizeof(char)));
	if (ft_strlen(s) < len + start)
		str = (char *)ft_calloc(ft_strlen(s) - start + 1, sizeof(char));
	else
		str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s[start + ++i] && i < len)
		str[i] = s[start + i];
	return (str);
}
