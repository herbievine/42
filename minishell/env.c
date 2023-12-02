/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/18 11:49:43 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_env_init function creates a copy of the environment variable
 * passed as a parameter. The copy is returned.
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_env_init(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (ft_free_array(copy, i), NULL);
	}
	copy[i] = NULL;
	char **cpy_env = ft_env_update_shlvl(copy);
	return(cpy_env);
}

/**
 * @brief The ft_env_get function returns the value of the environment variable
 * stored in the g_env variable. If the variable does not exist, NULL is
 * returned.
 *
 * @param key
 * @param envp
 * @return char*
 */
char	*ft_env_get(char **env, char *key)
{
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(key, env[i], ft_strlen(key)) == 0
			&& env[i][ft_strlen(key)] == '=')
			return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}

/**
 * @brief The ft_env_get_paths function returns an array of strings containing
 * the paths in the PATH environment variable. If the variable does not exist,
 * NULL is returned.
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_env_get_paths(char **env)
{
	char	*path;

	path = ft_env_get(env, "PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

/**
 * @brief TODO
 * 
 * @param env 
 * @return char* 
 */
char	*ft_env_get_home(char **env)
{
	char	*path;

	path = ft_env_get(env, "HOME");
	if (!path && __MACH__)
		path = ft_strjoin("/Users/", ft_env_get(env, "USER"));
	else if (!path)
		path = ft_strjoin("/home/", ft_env_get(env, "USER"));
	if (!path)
		return (NULL);
	return (path);
}

/**
 * @brief The ft_env_remove function removes the environment variable
 * passed as a parameter from the environment variable passed as a parameter.
 * The new environment variable is returned.
 * 
 * @param env 
 * @param key 
 * @return char** 
 */
char	**ft_env_remove(char ***env, char *key)
{
	int	i;
	int	j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[i][j] && (*env)[i][j] != '=')
			j++;
		if (ft_strncmp((*env)[i], key, j) == 0)
		{
			free((*env)[i]);
			while ((*env)[i])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			return (*env);
		}
		i++;
	}
	return (*env);
}
