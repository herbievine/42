/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:59:14 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:27:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_strjoin() function allocates (with malloc(3)) and returns a new
 * string, which is the result of the concatenation of 's1' and 's2'.
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dup;

	if (!s1 || !s2)
		return (0);
	dup = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	ft_strlcat(dup + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (dup);
}
