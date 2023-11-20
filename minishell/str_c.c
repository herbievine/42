/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:05:39 by herbie            #+#    #+#             */
/*   Updated: 2023/11/20 16:22:30 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "mem.h"

/**
 * @brief The str_c combines multiple strings into a single string. NULLs are
 * removed from the list of strings. The separator is placed between the
 * strings in the final string. The final string is allocated with malloc(3).
 * 
 * Inspired by the `str_c` function from the R language.
 * 
 * @param strs 
 * @param sep 
 * @return char* 
 */
char	*str_c(char **strs, char *sep)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = 0;
	i = -1;
	while (strs[++i])
		len += ft_strlen(strs[i]);
	len += ft_strlen(sep) * (i - 1);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	len = 0;
	i = -1;
	while (strs[++i])
	{
		ft_memcpy(str + len, strs[i], ft_strlen(strs[i]));
		len += ft_strlen(strs[i]);
		if (strs[i + 1])
		{
			ft_memcpy(str + len, sep, ft_strlen(sep));
			len += ft_strlen(sep);
		}
	}
	return (str);
}
