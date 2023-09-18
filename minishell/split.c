/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:23:13 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/17 18:50:43 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "mem.h"
#include "str.h"
#include "str2.h"
#include <stdlib.h>

static char		**ft_init_split(char const *s, char c);
static void		ft_fill_split(char const *s, char **split, char c);
static void		ft_free(char **split, size_t j);

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_init_split(s, c);
	if (!split)
		return (0);
	ft_fill_split(s, split, c);
	if (!split)
		return (0);
	return (split);
}

static char	**ft_init_split(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = 0;
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c && s[i - 1] != '\0')
			len++;
		i++;
	}
	if (s[i - 1] != c)
		len++;
	return ((char **)ft_calloc(len + 1, sizeof(char *)));
}

static void	ft_fill_split(char const *s, char **split, char c)
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
		{
			split[j++] = ft_substr(s, i - len, len);
			if (!split[j - 1])
			{
				ft_free(split, j);
				return ;
			}
		}
		if (s[i])
			i++;
	}
}

static void	ft_free(char **split, size_t j)
{
	if (j != -1)
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
