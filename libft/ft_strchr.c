/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:48:24 by hvine             #+#    #+#             */
/*   Updated: 2022/11/10 14:52:57 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if (!c)
		return ((char *)(s + ft_strlen(s)));
	while (++i < ft_strlen(s))
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (0);
}
