/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:38:15 by hvine             #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_strdup funtion allocates sufficient memory for a copy of the
 * string s1, does the copy, and returns a pointer to it. The pointer may
 * subsequently be used as an argument to the function free(3).
 * 
 * @param s 
 * @return char* 
 */
char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
