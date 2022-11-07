/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:48:24 by hvine             #+#    #+#             */
/*   Updated: 2022/11/07 15:19:20 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	write(1, "testing::", 9);
	if (*(s + ft_strlen(s)) == c)
		return (char *)(s + ft_strlen(s));
	write(1, "\n\nnothing found\n\n", 17);
	while (*s != c)
		s++;
	if (*s == 0)
		return (0);
	return (char *)(s);
}