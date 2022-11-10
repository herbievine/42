/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:38:15 by hvine             #+#    #+#             */
/*   Updated: 2022/11/10 15:19:35 by hvine            ###   ########.fr       */
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
