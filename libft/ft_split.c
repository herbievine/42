/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:59:50 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 10:50:15 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_init_list(char const *s, char c)
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

int	ft_insert_word_at_idx(char **list, char const *s, char c, size_t idx)
{
	size_t	i;
	size_t	len;

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

void	ft_put_str_into_list(char **list, char const *s, char c)
{
	size_t	i;
	size_t	idx;
	size_t	len;

	i = 0;
	idx = 0;
	len = 0;
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
}

char	**ft_split(char const *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	list = ft_init_list(s, c);
	ft_put_str_into_list(list, s, c);
	return (list);
}
