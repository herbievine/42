/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:23:13 by juliencros        #+#    #+#             */
/*   Updated: 2024/04/01 15:21:14 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "mem.h"
#include "str.h"
#include <stdlib.h>

static char	**ft_init_split(char const *s, char c, int with_sep);
static void	ft_fill_split(char const *s, char **split, char c, int with_sep);
static void	ft_free(char **split, size_t j);

char	**ft_split(char const *s, char c, int with_sep)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_init_split(s, c, with_sep);
	if (!split)
		return (0);
	ft_fill_split(s, split, c, with_sep);
	if (!split)
		return (0);
	return (split);
}

static char	**ft_init_split(char const *s, char c, int with_sep)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = 0;
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	while (s[i])
	{
		if ((s[i] == c && s[i -1] && s[i - 1] != c) || (with_sep && s[i] == c))
			len++;
		i++;
	}
	if (s[i - 1] != c)
		len++;
	return ((char **)ft_calloc(len + 2, sizeof(char *)));
}
//TODO: fix problem with len + 2

static void	ft_fill_split(char const *s, char **split, char c, int with_sep)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] != c)
			if (++i && ++len)
				continue ;
		if (len > 0)
			split[j++] = ft_substr(s, i - len, len + with_sep);
		else if (with_sep && s[i] == c && len == 0)
		{
			split[j] = ft_calloc(2, sizeof(char));
			split[j++][0] = c;
		}
		if (!split[j - 1] && j != 0)
			return (ft_free(split, j), (void)0);
		if (s[i])
			i++;
	}
}

static void	ft_free(char **split, size_t j)
{
	if (j != (size_t)(-1))
	{
		while (j)
		{
			free(split[j]);
			j--;
		}
		free(split);
	}
	else
		while (*split)
			free(*split++);
}
