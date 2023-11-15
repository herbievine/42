/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:57:47 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/14 16:07:35 by herbie           ###   ########.fr       */
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

bool	ft_set_env_from_arg(char ***env, char *arg)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_substr(arg, 0, ft_position(arg, '='));
	if (!key)
		return (false);
	value = ft_substr(arg, (ft_position(arg, '=') + 1), ft_strlen(arg));
	if (!value)
		return (free(key), false);
	ft_env_set(env, key, value);
	return (free(key), free(value), true);
}

int	ft_export(t_subcommand *subcommand, char ***env, t_token *token)
{
	int		i;
	char	*key;
	t_token	*head;

	i = 1;
	head = token;
	if (!subcommand->args[1])
		return (ft_env(*env, 1), 0);
	while (subcommand->args[i])
	{
		if (!ft_check_is_valid_identifier(subcommand->args[i], head->type))
			return (printf("not a valid identifier\n"), 1);
		else if (ft_strchr(subcommand->args[i], '='))
		{
			if (!ft_set_env_from_arg(env, subcommand->args[i]))
				return (1);
		}
		else
			ft_env_set(env, subcommand->args[i], NULL);
		i++;
		token = token->next;
	}
	return (0);
}

int	ft_unset(t_subcommand *subcommand, char ***env)
{
	char	**args;

	args = subcommand->args;
	while (*args)
		ft_env_remove(env, *args++);
	return (0);
}
