/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:59:50 by hvine             #+#    #+#             */
/*   Updated: 2023/04/18 14:12:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "str.h"
#include "mem.h"
#include "free.h"
#include <stdlib.h>

static char	**ft_init_list(char const *s, char c);
static void	ft_fill_list_with_strs(char **list, char const *s, char c);

/**
 * @brief The ft_split() function allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting 's' using the character 'c' as a delimiter.
 *
 * @param s
 * @param c
 * @return char**
 */
char	**ft_split(char const *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	list = ft_init_list(s, c);
	if (!list)
		return (0);
	ft_fill_list_with_strs(list, s, c);
	return (list);
}

static char	**ft_init_list(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	while (*++s)
		if (*s == c && *(s - 1) != c && *(s - 1) != '\0')
			i++;
	if (*--s != c)
		i++;
	return (ft_calloc(i + 1, sizeof(char *)));
}

static void	ft_fill_list_with_strs(char **list, char const *s, char c)
{
	size_t	i;
	size_t	idx;
	size_t	len;

	i = 0;
	idx = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			if (++i && ++len)
				continue ;
		if (len > 0)
		{
			list[idx++] = ft_substr(s, i - len, len);
			if (!list[idx - 1])
				return (ft_free_array(list, idx));
			len = 0;
		}
		if (s[i])
			i++;
	}
	list[idx] = NULL;
}
