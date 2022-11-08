/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:10:04 by herbie            #+#    #+#             */
/*   Updated: 2022/11/08 11:21:24 by hvine            ###   ########.fr       */
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

// int main()
// {
//     char src[] = "abcdef";
//     char dst[50] = "0123456789";
//     printf("%ld \n", ft_strlcat(dst, src, 25));
//     ft_strlcat(dst, src, 25);
//     printf("%s \n", dst);
// }