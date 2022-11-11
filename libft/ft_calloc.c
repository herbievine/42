/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:54:21 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:18:39 by herbie           ###   ########.fr       */
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

	if (nmemb * size < size)
		return (NULL);
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}
