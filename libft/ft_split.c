/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:59:50 by hvine             #+#    #+#             */
/*   Updated: 2022/11/09 08:10:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_init_list(char const *s, char c)
{
	size_t i;

	i = 0;
	while (*++s)
		if (*s == c && *(s - 1) != c && *(s - 1) != '\0')
			i++;
	if (*--s != c)
		i++;

	return (ft_calloc(i + 1, sizeof(char *)));
}

int ft_insert_word_at_idx(char **list, char const *s, char c, size_t idx)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (s[i] && s[i] != c)
		if (++i && ++len)
			continue ;
	if (len > 0)
	{
		list[idx++] = ft_substr(s, i - len, len);
		len = 0;
	}

	return (len);
}

char **ft_split(char const *s, char c)
{
	size_t i;
	size_t idx;
	size_t len;
	char **list;

	i = 0;
	idx = 0;
	len = 0;
	list = ft_init_list(s, c);
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				if (++i && ++len)
					continue ;
			if (len > 0)
			{
				list[idx++] = ft_substr(s, i - len, len);
				len = 0;
			}
		}
		if (s[i])	
			i++;
	}

	return (list);
}