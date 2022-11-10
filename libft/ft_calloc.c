/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:54:21 by herbie            #+#    #+#             */
/*   Updated: 2022/11/10 14:37:08 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;

	if (nmemb * size < size)
		return (NULL);
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}
