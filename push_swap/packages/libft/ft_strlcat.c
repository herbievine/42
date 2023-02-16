/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:10:04 by herbie            #+#    #+#             */
/*   Updated: 2022/11/12 15:53:53 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strlcat() function appends string src to the end of dst. It will
 * append at most size - strlen(dst) - 1 bytes, NULL-terminating the result.
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = -1;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (0);
	if (size < dest_len || !size)
		return (size + src_len);
	while (src[++i] && i + 1 < (size - dest_len))
		dst[dest_len + i] = src[i];
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
