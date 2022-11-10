/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:47:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/10 14:48:00 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if ((long int)src > (long int)dest)
		while (++i < len)
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	else
		return (ft_memcpy(dest, src, len));
	return (dest);
}
