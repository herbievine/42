/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:15:16 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief The ft_bzero funtion writes n zeroed bytes to the string s. If n is
 * zero, ft_bzero() does nothing.
 *
 * @param s
 * @param n
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/**
 * @brief The ft_calloc funtion allocates memory for an array of nmemb
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

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	space = malloc(nmemb * size);
	if (!space)
		return (0);
	ft_bzero(space, nmemb * size);
	return (space);
}

/**
 * @brief The memset funtion writes len bytes of value c (converted to an
 * unsigned char) to the string b.
 *
 * @param s
 * @param c
 * @param n
 * @return void*
 */
void	*ft_memset(void *s, int c, size_t n)
{
	while (n-- > 0)
		((char *)s)[n] = (unsigned char)c;
	return (s);
}

/**
 * @brief The memcpy funtion copies n bytes from memory area src to memory
 * area dst. If dst and src overlap, behavior is undefined.  Applications in
 * which dst and src might overlap should use memmove(3) instead.
 *
 * @param dest
 * @param src
 * @param n
 * @return void*
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (0);
	while (n--)
		((unsigned char *)dest)[n] = ((char *)src)[n];
	return (dest);
}
