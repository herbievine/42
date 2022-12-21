/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:48 by herbie            #+#    #+#             */
/*   Updated: 2022/12/17 15:03:44 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief The ft_strlen() function computes the length of the string s.
 *
 * @param s
 * @return size_t
 */
size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief The ft_strchr() function locates the first occurrence of c (converted
 * to a char) in the string pointed to by s. The terminating null character is
 * considered to be part of the string; therefore if c is '\0', the functions
 * locate the terminating '\0'.
 *
 * @param s
 * @param c
 * @return char*
 */
char *ft_strchr(const char *s, int c)
{
	size_t i;

	i = -1;
	if (!c)
		return ((char *)(s + ft_strlen(s)));
	while (++i < ft_strlen(s))
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (0);
}

/**
 * @brief The ft_strlcpy() function copies up to 'size' - 1 characters from the
 * NUL-terminated string 'src' to 'dst', NUL-terminating the result.
 *
 * @param dst
 * @param src
 * @param size
 * @return size_t
 */
size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = -1;
	if (size == 0)
		return (ft_strlen(src));
	while (src[++i] && i < size - 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}

/**
 * @brief The ft_strjoin() function allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation of 's1' and 's2'.
 *
 * @param s1
 * @param s2
 * @return char*
 */
char *ft_strjoin(char const *s1, char const *s2)
{
	char *dup;
	size_t i;

	if (!s1 || !s2)
		return (0);
	dup = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dup)
		return (0);
	dup[ft_strlen(s1) + ft_strlen(s2)] = 0;
	i = ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	while (*s2)
		dup[i++] = *s2++;
	return (dup);
}

/**
 * @brief The ft_strdup() function allocates sufficient memory for a copy of the
 * string s1, does the copy, and returns a pointer to it. The pointer may
 * subsequently be used as an argument to the function free(3).
 *
 * @param s
 * @return char*
 */
char *ft_strdup(const char *s)
{
	char *dup;

	dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}