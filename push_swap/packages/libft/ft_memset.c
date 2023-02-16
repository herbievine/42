/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:08:36 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:06:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memset() function writes len bytes of value c (converted to an
 * unsigned char) to the string b.
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void	*ft_memset(void *s, int c, size_t n)
{
	while (n-- > 0)
		((char *)s)[n] = (unsigned char)c;
	return (s);
}
