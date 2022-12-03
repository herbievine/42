/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:48 by herbie            #+#    #+#             */
/*   Updated: 2022/11/30 15:34:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief The ft_strlen() function computes the length of the string s up to
 * char c.
 *
 * @param s
 * @return size_t
 */
size_t ft_strnlen(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
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
	int i;
	char *dup;

	if (!s1 || !s2)
		return (0);
	i = -1;
	dup = (char *)malloc((ft_strnlen(s1, 0) + ft_strnlen(s2, 0) + 1) * sizeof(char));
	if (!dup)
		return (0);
	dup[i] = 0;
	while (*s1)
		dup[++i] = *s1++;
	while (*s2)
		dup[++i] = *s2++;
	return (dup);
}