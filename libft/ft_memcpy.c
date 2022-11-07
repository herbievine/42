/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:28:28 by herbie            #+#    #+#             */
/*   Updated: 2022/11/07 15:37:46 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *dst_cpy;

	dst_cpy = (unsigned char *)dest;
	while (n-- > 0)
		dst_cpy[n] = ((char *)src)[n];

	return dest;
}
