/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:39:32 by hvine             #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_strnstr funtion locates the first occurrence of the null-
 * terminated string needle in the string haystack, where not more than len
 * characters are searched. Characters that appear after a '\0' character are
 * not searched.
 * 
 * @param haystack 
 * @param needle 
 * @param len 
 * @return char* 
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!*little)
		return ((char *)big);
	if (!len)
		return (0);
	while (*big && len--)
	{
		if (
			ft_strncmp(big, little, ft_strlen(little)) == 0
			&& ft_strlen(little) <= len + 1
		)
			return ((char *)big);
		big++;
	}
	return (0);
}
