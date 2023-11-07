/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:42:57 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/04 13:34:53 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>

char	**ft_add_cpy_env_var(char *key, char *value, char ***envp)
{
	int		i;
	char	**head;
	char	*full_str;

	i = -1;
	head = *envp;
	while (head[++i])
	{
		if (ft_strncmp(head[i], key, ft_strlen(key)) == 0)
		{
			if (value)
			{
				free(head[i]);
				full_str = ft_strjoin(key, value);
				head[i] = ft_strdup(full_str);
				free(full_str);
			}
			return (*envp);
		}
	}
	return (ft_create_cpy_var(key, value, envp, i));
}

char	**ft_create_cpy_var(char *key, char *value, char ***envp, int i)
{
	char	*full_str;
	char	**head;
	char	**new_cpy_envp;

	head = *envp;
	new_cpy_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_cpy_envp)
		return (*envp);
	i = -1;
	while (head[++i])
		new_cpy_envp[i] = ft_strdup(head[i]);
	if (value)
	{
		full_str = ft_strjoin(key, value);
		new_cpy_envp[i++] = ft_strdup(full_str);
	}
	else
	{
		full_str = ft_strjoin(key, "\"\"");
		new_cpy_envp[i++] = ft_strdup(full_str);
	}
	free(full_str);
	new_cpy_envp[i] = NULL;
	*envp = new_cpy_envp;
	return (new_cpy_envp);
}

void	ft_change_exit_status(t_subcommand *subcommand)
{
	char	*str;

	str = ft_itoa(g_signal);
	ft_add_cpy_env_var("?=", str, &subcommand->cpy_envp);
	free(str);
}
