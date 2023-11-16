/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:42:57 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/16 15:01:45 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

static char	**ft_env_set_at_index(char *key, char *value, char **env, int i);
static char	*ft_env_format(char *key, char *value);

char	**ft_env_set(char **env, char *key, char *value)
{
	int	i;
	char	*str_fmt;

	i = -1;
	while (env[++i])
	{
		// TODO Make sure the token `+ 1` is a `=`
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 )
		{
			if (value)
			{
				str_fmt = ft_env_format(key, value);
				if (!str_fmt)
					return env;
				free(env[i]);
				env[i] = ft_strdup(str_fmt);
				free(str_fmt);
			}
			return (env);
		}
	}
	return (ft_env_set_at_index(key, value, env, i));
}

static char	*ft_env_format(char *key, char *value)
{
	char	*tmp;
	char	*str_fmt;

	if (!value)
	{
		value = ft_calloc(3, sizeof(char));
		if (!value)
			return (NULL);
		value[0] = '"';
		value[1] = '"';
		value[2] = '\0';
	}
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	str_fmt = ft_strjoin(tmp, value);
	free(tmp);
	if (!str_fmt)
		return (NULL);
	return (str_fmt);
}

static char	**ft_env_set_at_index(char *key, char *value, char **env, int i)
{
	char	*full_str;
	char	**new_env;

	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (env);
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_free_array(new_env, i), env);
	}
	full_str = ft_env_format(key, value);
	if (!full_str)
		return (ft_free_array(new_env, i), env);
	new_env[i] = ft_strdup(full_str);
	if (!new_env[i])
		return (free(full_str), ft_free_array(new_env, i - 1), env);
	new_env[i + 1] = NULL;
	return (free(full_str), ft_free_array(env, i), new_env);
}
