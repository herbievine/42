/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:54:21 by herbie            #+#    #+#             */
/*   Updated: 2022/11/12 16:11:30 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_calloc() function allocates memory for an array of nmemb
 * elements of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero.
 * 
 * @param nmemb 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;

	if (nmemb && nmemb > SIZE_MAX / size)
		return (0);
	space = malloc(nmemb * size);
	if (!space)
		return (0);
	ft_bzero(space, nmemb * size);
	return (space);
}
