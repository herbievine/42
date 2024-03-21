/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:41:08 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/18 17:29:35 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!new)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[i + j])
		j++;
	while (j && ft_strchr(set, s1[i + j - 1]))
		j--;
	while (k < j)
	{
		new[k] = s1[i + k];
		k++;
	}
	new[k] = '\0';
	return (new);
}

int	ft_strschr(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[i])
	{
		j = 0;
		if (s2[i] == s1[j])
		{
			while (s1[j] && s2[i] == s1[j])
			{
				i++;
				j++;
			}
			if (j == (int)ft_strlen(s1))
				return (i - j);
		}
		i++;
	}
	return (-1);
}

int	ft_strchr_array(char **sep, char *str)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (ft_strschr(sep[i], str) != -1)
			return (ft_strschr(sep[i], str));
		i++;
	}
	return (-1);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}