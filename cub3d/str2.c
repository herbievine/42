/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:41:08 by juliencros        #+#    #+#             */
/*   Updated: 2024/04/05 17:50:34 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdio.h>

/**
 * @brief The function return a duplicate of the string s without 
 * 	the set characters at the beginning and the end of the string.
 * 	The function does not search for the set characters in the middle
 * 	of the string.
 * 	It uses malloc.
 * @param s string
 * @return size_t
*/
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

/**
 * @brief The function return the index of the the first occurence
 * 	of the string s1 in the string s2, -1 otherwise.
 * @param s1 string
 * @param s2 string
 * @return int
*/
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
			while (s2[i] && s1[j] && s1[j] && s2[i] == s1[j])
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

/**
 * @brief The function return the index of the first character
 * of the string s2 in the string s1.
 * @param sep array of separator
 * @param string
*/
int	ft_strchr_array(char **sep, char *str)
{
	int	i;

	i = 0;
	if (!sep || !str)
		return (-1);
	while (sep[i])
	{
		if (ft_strschr(sep[i], str) != -1)
			return (ft_strschr(sep[i], str));
		i++;
	}
	return (-1);
}

/**
 * @brief The function return the duplicate of the string s
 * by using calloc.
 * It uses malloc.
 * @param string
 * @return char*
*/
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
