/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:20:45 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 20:59:41 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static char	**ft_init_list(char const *s, char c);
static void	ft_fill_list_with_strs(char **list, char const *s, char c);
static void	ft_free_list(char **list, size_t idx);

/**
 * @brief The ft_split() function allocates (with malloc(3)) and returns an array
 * of strings obtained by splitting 's' using the character 'c' as a delimiter.
 * 
 * @param s 
 * @param c 
 * @return char** 
 */
char	**ft_split(char const *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	list = ft_init_list(s, c);
	if (!list)
		return (0);
	ft_fill_list_with_strs(list, s, c);
	return (list);
}

static char	**ft_init_list(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	while (*++s)
		if (*s == c && *(s - 1) != c && *(s - 1) != '\0')
			i++;
	if (*--s != c)
		i++;
	return (ft_calloc(i + 1, sizeof(char *)));
}

static void	ft_fill_list_with_strs(char **list, char const *s, char c)
{
	size_t	i;
	size_t	idx;
	size_t	len;

	i = 0;
	idx = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			if (++i && ++len)
				continue ;
		if (len > 0)
		{
			list[idx++] = ft_substr(s, i - len, len);
			if (!list[idx - 1])
			{
				ft_free_list(list, idx);
				return ;
			}
			len = 0;
		}
		if (s[i])
			i++;
	}
}

static void	ft_free_list(char **list, size_t idx)
{
	while (idx--)
		free(list[idx]);
	free(list);
}

/**
 * @brief The ft_strlen() function computes the length of the string s.
 *
 * @param s
 * @return size_t
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/**
 * @brief The ft_atoi() function converts the initial portion of the string
 * pointed to by nptr to int representation.
 *
 * @param nptr
 * @return int
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
		if (nptr[i++] == 45)
			sign *= -1;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * sign);
}