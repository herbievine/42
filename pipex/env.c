/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:38:50 by herbie            #+#    #+#             */
/*   Updated: 2023/04/26 17:48:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include <stdlib.h>

/**
 * @brief The ft_get_env function returns the value of the environment variable
 * whose name is passed as an argument. If the variable does not exist, NULL is
 * returned.
 * 
 * @param key 
 * @param envp 
 * @return char* 
 */
char	*ft_get_env(char *key, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			return (ft_strchr(envp[i], '=') + 1);
	return (NULL);
}

/**
 * @brief The ft_get_paths function returns an array of strings containing the
 * paths in the PATH environment variable. If the variable does not exist, NULL
 * is returned.
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_get_paths(char **envp)
{
	char	*path;

	path = ft_get_env("PATH", envp);
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}
