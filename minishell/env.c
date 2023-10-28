/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/28 11:29:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "str2.h"
#include "split.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_get_cpy_env function returns the value of the environment variable
 * stored in the g_env variable. If the variable does not exist, NULL is
 * returned.
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
			free(subcommand->cpy_envp[i]); // TODO make sure this gets added
			subcommand->cpy_envp[i] = ft_strjoin(key, value);
			return ;
		}
		i++;
	}
	return ;
}

// void	ft_remove_cpy_env(t_subcommand *subcommand, char *key)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (subcommand->cpy_envp[i])
// 	{
// 		j = 0;
// 		while (subcommand->cpy_envp[i][j] && subcommand->cpy_envp[i][j] != '=')
// 			j++;
// 		if (ft_strncmp(subcommand->cpy_envp[i], key, j) == 0)
// 		{
// 			free(subcommand->cpy_envp[i]); // TODO make sure this gets removed
// 			while (subcommand->cpy_envp[i])
// 			{
// 				subcommand->cpy_envp[i] = subcommand->cpy_envp[i + 1];
// 				i++;
// 			}
// 			return ;
// 		}
// 		i++;
// 	}
// 	return ;
// }

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
	cpy_envp = malloc(sizeof(char *) * (i + 1));
	if (!cpy_envp)
		return (NULL);
	i = -1;
	while (envp[++i])
		cpy_envp[i] = ft_strdup(envp[i]);
	cpy_envp[i] = NULL;
	return (cpy_envp);
}

char	**ft_remove_cpy_env_var(char **cpy_envp, char *key)
{
	int i;
	int j;

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

void	ft_add_cpy_env_var(t_subcommand *subcommand, char *value)
{
	int		i;
	int		j;
	char	**new_cpy_envp;
	char *key;
	char *tmp;

	i = 0;
	if (ft_strchr(value, '='))
		key  = ft_substr(value, 0, ft_strchr(value, '=') - value + 1);
	while(subcommand->cpy_envp[i])
	{
		if (key && ft_strncmp(subcommand->cpy_envp[i], key, ft_strlen(key)) == 0)
		{
			tmp = subcommand->cpy_envp[i];
			free(key);
			key = ft_substr(value, ft_position(value, '=') + 1, ft_strlen(value) - ft_position(value, '=') + 1);
			subcommand->cpy_envp[i] = ft_strjoin(subcommand->cpy_envp[i], key);
			free(tmp);
			free(key);
			return ;
		}
		i++;
	}
	new_cpy_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_cpy_envp)
		return ;
	i = -1;
	while (subcommand->cpy_envp[++i])
		new_cpy_envp[i] = ft_strdup(subcommand->cpy_envp[i]);
	new_cpy_envp[i++] = ft_strjoin(value, "=");
	new_cpy_envp[i] = NULL;
	ft_free_array(subcommand->cpy_envp, -1);
	subcommand->cpy_envp = new_cpy_envp;
	return ;
}