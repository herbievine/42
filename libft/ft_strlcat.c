/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:10:04 by herbie            #+#    #+#             */
/*   Updated: 2022/11/10 11:53:41 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dest_len;
	size_t src_len;

	i = -1;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size <= dest_len)
		return (size + src_len);
	while (src[++i] && i + 1 < (size - dest_len))
		dst[dest_len + i] = src[i];
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
