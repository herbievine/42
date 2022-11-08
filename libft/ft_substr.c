/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:30:40 by hvine             #+#    #+#             */
/*   Updated: 2022/11/08 18:36:49 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	int i;
	char *str;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) < len + start)
		str = (char *)ft_calloc(ft_strlen(s) - start + 1, sizeof(char));
	else 
		str = (char *)ft_calloc(len + 1, sizeof(char));	
	if (!str)
		return (0);
	i = -1;
	while (s[start + ++i] && i < len)
		str[i] = s[start + i];

	return (str);
}