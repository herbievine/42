/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:57:05 by herbie            #+#    #+#             */
/*   Updated: 2022/10/23 12:45:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1_cpy;
	const unsigned char *s2_cpy;

	s1_cpy = (const unsigned char *)s1;
	s2_cpy = (const unsigned char *)s2;

	if (n == 0)
		return 0;
	while (n-- > 0)
	{
		if (*s1_cpy != *s2_cpy)
			return *s1_cpy - *s2_cpy;

		s1_cpy++;
		s2_cpy++;
	}

	return 0;
}