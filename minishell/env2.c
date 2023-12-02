/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:42:57 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/27 09:27:55 by juliencros       ###   ########.fr       */
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
	int		i;
	char	*str_fmt;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0
			&& env[i][ft_strlen(key)] == '=')
		{
			if (value)
			{
				str_fmt = ft_env_format(key, value);
				if (!str_fmt)
					return (env);
				free(env[i]);
				env[i] = ft_strdup(str_fmt);
				free(str_fmt);
			}
			return (env);
		}
	}
	return (ft_env_set_at_index(key, value, env, i));
}

char	**ft_env_update_shlvl(char **env)
{
	char	*shlvl;
	char	*tmp;

	shlvl = ft_env_get(env, "SHLVL");
	if (!shlvl)
		return (env);
	tmp = ft_itoa(ft_atoi(shlvl) + 1);
	if (!tmp)
		return (env);
	env = ft_env_set(env, "SHLVL", tmp);
	free(tmp);
	return (env);
}

static char	*ft_env_format(char *key, char *value)
{
	char	*tmp;
	char	*str_fmt;
	char	*empty_value;

	empty_value = NULL;
	if (!value)
	{
		empty_value = ft_strdup("\"\"");
		if (!empty_value)
			return (NULL);
	}
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	if (!value)
		str_fmt = ft_strjoin(tmp, empty_value);
	else
		str_fmt = ft_strjoin(tmp, value);
	if (empty_value)
		free(empty_value);
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
