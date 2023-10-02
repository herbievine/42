/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:40 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/02 12:14:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include <stdlib.h>

/**
 * @brief The ft_get_env function returns the value of the environment variable
 * stored in the g_env variable. If the variable does not exist, NULL is
 * returned.
 *
 * @param key
 * @param envp
 * @return char*
 */
char	*ft_get_env(char *key)
{
	int		i;
	char	**envp;

	i = -1;
	envp = g_env;
	while (envp[++i])
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
	return (NULL);
}

void	ft_set_env(char *key, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (g_env[i][j] && g_env[i][j] != '=')
			j++;
		if (ft_strncmp(g_env[i], key, j) == 0)
		{
			free(g_env[i]); // TODO make sure this gets added
			g_env[i] = ft_strjoin(key, value);
			return ;
		}
		i++;
	}
	return ;
}

void	ft_remove_env(char *key)
{
	int	i;
	int	j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (g_env[i][j] && g_env[i][j] != '=')
			j++;
		if (ft_strncmp(g_env[i], key, j) == 0)
		{
			free(g_env[i]); // TODO make sure this gets removed
			while (g_env[i])
			{
				g_env[i] = g_env[i + 1];
				i++;
			}
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
char	**ft_get_paths(void)
{
	char	*path;

	path = ft_get_env("PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}
