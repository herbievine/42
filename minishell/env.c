/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/21 17:04:12 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include <stdlib.h>


char	*ft_get_env(char *name, t_subcommand *subcommand)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (global_env[i])
	{
		j = 0;
		while (global_env[i][j] && global_env[i][j] != '=')
			j++;
		if (ft_strncmp(global_env[i], name, ft_strlen(name)) == 0)
			return (global_env[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	ft_add_env(char *name, char *value, t_subcommand *subcommand)
{
	int		i;
	int		j;

	i = 0;
	while (global_env[i])
	{
		j = 0;
		while (global_env[i][j] && global_env[i][j] != '=')
			j++;
		if (ft_strncmp(global_env[i], name, j) == 0)
		{
			free(global_env[i]);
			global_env[i] = ft_strjoin(name, value);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_remove_env(char *name, t_subcommand *subcommand)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (global_env[i])
	{
		j = 0;
		while (global_env[i][j] && global_env[i][j] != '=')
			j++;
		if (ft_strncmp(global_env[i], name, j) == 0)
		{
			free(global_env[i]);
			while (global_env[i])
			{
				global_env[i] = global_env[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}