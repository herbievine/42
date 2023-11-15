/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:57:47 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 18:01:54 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "env.h"
#include "display.h"
#include "str.h"
#include "builtins_func_utils.h"
#include "signals.h"
#include "token.h"
#include "free.h"
#include "history.h"
#include "find_cmds.h"
#include "char.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

bool	ft_set_key_value(t_subcommand *subcommand, char ***envp, int i)
{
	char	*key;
	char	*value;

	if ((ft_position(subcommand->args[i], '='))
		< ft_strlen(subcommand->args[i]))
		key = ft_substr(subcommand->args[i],
				(ft_position(subcommand->args[i], '=') + 1),
				ft_strlen(subcommand->args[i]));
	else
		key = NULL;
	value = ft_fmt_path("\"", key, "\"");
	free(key);
	key = ft_substr(subcommand->args[i], 0,
			ft_position(subcommand->args[i], '=') + 1);
	*envp = ft_add_cpy_env_var(key, value, envp);
	free(key);
	free(value);
	return (true);
}

int	ft_export(t_subcommand *subcommand, char ***envp, t_token *token)
{
	int		i;
	char	*key;
	t_token	*head;

	i = 1;
	head = token;
	if (!subcommand->args[1])
		return (ft_env(envp, 1), 0);
	while (subcommand->args[i])
	{
		if (!ft_check_is_valid_identifier(subcommand->args[i], head->type))
			return (ft_putstr_fd(" not a valid identifier\n", 2), 1);
		else if (ft_strchr(subcommand->args[i], '='))
		{
			if (!ft_set_key_value(subcommand, envp, i))
				return (1);
		}
		else
		{
			key = ft_strjoin(subcommand->args[i], "=");
			*envp = ft_add_cpy_env_var(key, NULL, envp);
		}
		i++;
		token = token->next;
	}
	return (0);
}

int	ft_unset(t_subcommand *subcommand, char ***envp)
{
	char	**args;

	args = subcommand->args;
	while (*args)
		*envp = ft_remove_cpy_env_var(*envp, *args++);
	return (0);
}
