/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:18:12 by herbie            #+#    #+#             */
/*   Updated: 2022/11/08 16:05:18 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(char const *s1, char const *set)
{
	int i;
	int len;
	char *str;

	i = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]))
		i++;
	if (s1[len - 1])
		while (ft_strchr(set, s1[len - 1]))
			len--;
	str = (char *)ft_calloc(len - i, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1 + i, len - i + 1);
	printf("\n\n\n\nstr = \"%s\", i = %d, len = %d, out = \"%s\"\n", s1, i, len, str);
	printf("char is %c\n", s1[len - 1]);
	return (str);
}