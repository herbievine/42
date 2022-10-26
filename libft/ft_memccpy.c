/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:12:52 by herbie            #+#    #+#             */
/*   Updated: 2022/10/23 11:47:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char *dst_cpy;
	const char *src_cpy;

	dst_cpy = dst;
	src_cpy = src;
	while (n-- > 0)
		if ((*dst_cpy++ = *src_cpy++) == (char)c)
			return dst_cpy;
	return 0;
}