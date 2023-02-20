/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:49:53 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 21:58:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "strings.h"

int *ft_parse_args(int argc, char **argv)
{
	int	i;
	int	*args;

	i = -1;
	if (argc == 2)
		args = ft_get_args_from_string(argv[1]);
	else
	{
		args = malloc(sizeof(int) * (argc - 1));
		while (++i < argc - 1)
			args[i] = ft_atoi(argv[i + 1]);
	}
	return (args);
}

int	*ft_get_args_from_string(char *str)
{
	int	*args;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			j++;
		i++;
	}
	args = malloc(sizeof(int) * (j + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			args[k] = ft_atoi(str + i - j);
			j = 0;
			k++;
		}
		else
			j++;
		i++;
	}
	args[k] = ft_atoi(str + i - j);
	return (args);
}