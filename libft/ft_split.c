/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:59:50 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 21:27:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_init_list(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*++s)
		if (*s == c && *(s - 1) != c && *(s - 1) != '\0')
			i++;
	if (*--s != c)
		i++;
	return (ft_calloc(i + 1, sizeof(char *)));
}

static void	ft_free_list(char **list, size_t idx)
{
	while (idx--)
		free(list[idx]);
	free(list);
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
			{
				ft_free_list(list, idx);
				return ;
			}
			len = 0;
		}
		if (s[i])
			i++;
	}
}

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
