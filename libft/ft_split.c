/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:59:50 by hvine             #+#    #+#             */
/*   Updated: 2022/11/08 19:47:56 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_init_list(char const *s, char c)
{
	size_t i;

	printf("total count for \"%s\" with \"%c\" is", s, c);

	i = 0;
	while (*++s)
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0' && s++)
			i++;

	printf(" %zu\n", i);

	return (malloc(sizeof(char *) * (i + 1)));
}

char **ft_split(char const *s, char c)
{
	size_t i;
	char **list;

	i = 0;
	list = ft_init_list(s, c);
	// while (*s)
	// {
	// 	if (*s)
	// }
}

// test split
int main()
{
	char *s = "dsss,ello,world,,,ss";
	char c = ',';
	char **list = ft_split(s, c);
	int i = 4;
	while (i--)
		printf("%s ", *list++);
}