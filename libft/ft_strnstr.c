/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:39:32 by hvine             #+#    #+#             */
/*   Updated: 2022/11/10 11:44:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		if (ft_strncmp(big, little, ft_strlen(little)) == 0 && ft_strlen(little) <= len + 1)
			return ((char *)big);
		big++;
	}

	return (0);
}
