/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/18 10:18:20 by juliencros       ###   ########.fr       */
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
	while (subcommand->envp[i])
	{
		j = 0;
		while (subcommand->envp[i][j] && subcommand->envp[i][j] != '=')
			j++;
		if (ft_strncmp(subcommand->envp[i], name, j) == 0)
			return (subcommand->envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	ft_add_env(char *name, char *value, t_subcommand *subcommand)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (subcommand->envp[i])
	{
		j = 0;
		while (subcommand->envp[i][j] && subcommand->envp[i][j] != '=')
			j++;
		if (ft_strncmp(subcommand->envp[i], name, j) == 0)
		{
			free(subcommand->envp[i]);
			subcommand->envp[i] = ft_strjoin(name, value);
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
	while (subcommand->envp[i])
	{
		j = 0;
		while (subcommand->envp[i][j] && subcommand->envp[i][j] != '=')
			j++;
		if (ft_strncmp(subcommand->envp[i], name, j) == 0)
		{
			free(subcommand->envp[i]);
			while (subcommand->envp[i])
			{
				subcommand->envp[i] = subcommand->envp[i + 1];
				i++;
			}
			return (0);
		}
		i++;
	}
	return (0);
}