/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:39:32 by hvine             #+#    #+#             */
/*   Updated: 2022/11/08 08:26:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *big, const char *little, size_t len)
{
	// printf("\n\n\n\n\n\ninput: %s, %s, %zu\n", big, little, len);

	// printf("output 1: %s\n", strnstr(big, little, len));

	if (!*little)
		return ((char *)big);
	while (*big && len--)
	{
		if (ft_strncmp(big, little, ft_strlen(little)) == 0)
		{
			// printf("output 2: %s\n\n", big);
			return ((char *)big);
		}
		big++;
	}

	// printf("output 2: (null)\n");
	return (0);
}

// char *ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	int i = 0;
// 	int j = 0;

// 	while (big[i] && i < len)
// 	{
// 		while (big[i + j] == little[j] && i + j < len)
// 		{
// 			if (little[j + 1] == '\0')
// 				return ((char *)big + i);
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}

// 	return (0);
// }