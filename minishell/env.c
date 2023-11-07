/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/04 14:21:58 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_get_cpy_env function returns the value of 
 * the environment variable stored in the g_env variable. 
 * If the variable does not exist, NULL is returned.
 *
 * @param key
 * @param envp
 * @return char*
 */
char	*ft_get_cpy_env(t_subcommand *subcommand, char *key)
{
	int		i;

	i = -1;
	while (subcommand->cpy_envp[++i])
		if (ft_strncmp(key, subcommand->cpy_envp[i], ft_strlen(key)) == 0
			&& subcommand->cpy_envp[i][ft_strlen(key)] == '=')
			return (ft_strchr(subcommand->cpy_envp[i], '=') + 1);
	return (NULL);
}

void	ft_set_cpy_env(t_subcommand *subcommand, char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (subcommand->cpy_envp[i])
	{
		j = 0;
		while (subcommand->cpy_envp[i][j] && subcommand->cpy_envp[i][j] != '=')
			j++;
		if (ft_strncmp(subcommand->cpy_envp[i], key, j) == 0)
		{
			free(subcommand->cpy_envp[i]);
			subcommand->cpy_envp[i] = ft_strjoin(key, value);
			return ;
		}
		i++;
	}
	return ;
}

/**
 * @brief The ft_get_paths function returns an array of strings containing the
 * paths in the PATH environment variable. If the variable does not exist, NULL
 * is returned.
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_get_paths(t_subcommand *subcommand)
{
	char	*path;

	path = ft_get_cpy_env(subcommand, "PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	**ft_cpy_env(char **envp)
{
	int		i;
	char	**cpy_envp;

	i = 0;
	while (envp[i])
		i++;
	cpy_envp = malloc(sizeof(char *) * (i + 2));
	if (!cpy_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		cpy_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy_envp[i++] = ft_strdup("?=0");
	cpy_envp[i] = NULL;
	return (cpy_envp);
}

char	**ft_remove_cpy_env_var(char **cpy_envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (cpy_envp[i])
	{
		j = 0;
		while (cpy_envp[i][j] && cpy_envp[i][j] != '=')
			j++;
		if (ft_strncmp(cpy_envp[i], key, j) == 0)
		{
			free(cpy_envp[i]);
			while (cpy_envp[i])
			{
				cpy_envp[i] = cpy_envp[i + 1];
				i++;
			}
			return (cpy_envp);
		}
		i++;
	}
	return (cpy_envp);
}
