/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:38:15 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 17:51:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
