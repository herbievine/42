/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:51:57 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:13:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memchr() function locates the first occurrence of c (converted to
 * an unsigned char) in string s.
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (((char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
	return (0);
}
