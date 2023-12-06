/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:04:11 by codespace         #+#    #+#             */
/*   Updated: 2023/12/06 14:59:18 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../char.h"
#include "../str.h"
#include "../display.h"
#include "../env.h"
#include <stdlib.h>

static bool	ft_parse_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '$' || str[i] == '-')
			return (false);
		if (str[i] && str[i] == '=' && ((i > 0 && !ft_isalnum(str[i - 1]))))
			return (false);
		i++;
	}
	if (!i)
		return (false);
	return (true);
}

static void	ft_print_exported_variables(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static bool	ft_set_env_from_arg(char ***env, char *arg)
{
	char	*key;
	char	*value;
	int		equal_pos;

	equal_pos = 0;
	while (arg[equal_pos] && arg[equal_pos] != '=')
		equal_pos++;
	key = ft_substr(arg, 0, equal_pos);
	if (!key)
		return (false);
	value = ft_substr(arg, equal_pos + 1, ft_strlen(arg));
	if (!value)
		return (free(key), false);
	*env = ft_env_set(*env, key, value);
	return (free(key), free(value), true);
}

int	ft_export(t_command *cmd, t_subcommand *subcommand, t_token *token)
{
	int	i;

	i = 0;
	if (!subcommand->args[1])
		return (ft_print_exported_variables(*(cmd->env)), 0);
	while (subcommand->args[++i])
	{
		if (!ft_parse_export(subcommand->args[i]))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			g_signal = 1;
			continue ;
		}
		else if (ft_strchr(subcommand->args[i], '='))
		{
			if (!ft_set_env_from_arg(cmd->env, subcommand->args[i]))
				return (1);
		}
		else
			*(cmd->env) = ft_env_set(*(cmd->env), subcommand->args[i], NULL);
		token = token->next;
	}
	if (g_signal == 1)
		return (1);
	return (0);
}
