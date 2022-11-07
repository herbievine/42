/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:12:52 by herbie            #+#    #+#             */
/*   Updated: 2022/11/07 15:36:37 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char *dst_cpy;
	const char *src_cpy;

	dst_cpy = dest;
	src_cpy = src;
	while (n-- > 0)
		if ((*dst_cpy++ = *src_cpy++) == (char)c)
			return dst_cpy;
	return 0;
}