/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:48:24 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 15:31:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	size_t i;

	i = -1;
	if (!c)
		return (char *)(s + ft_strlen(s));
	while (++i < ft_strlen(s))
		if (s[i] == (char)c)
			return (char *)(s + i);
	return (0);
}