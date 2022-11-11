/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:40:08 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 21:13:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_strrchr() function locates the last occurrence of 'c' (converted
 * to a char) in the string pointed to by 's'. The terminating null character is
 * considered to be part of the string; therefore if 'c' is `\0', the functions
 * locate the terminating `\0'.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) + 1;
	while (i-- > 0)
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (0);
}
