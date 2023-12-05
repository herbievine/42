/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:04:11 by codespace         #+#    #+#             */
/*   Updated: 2023/12/05 21:10:59 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../char.h"
#include "../str.h"
#include "../display.h"
#include "../env.h"
#include <stdlib.h>

static int ft_check_is_valid_identifier(char *str, int type)
{
	int i;

	i = 0;
	(void)type;
	// if (type == TOKEN_DQ || type == TOKEN_SQ)
	// return (false);
	if (ft_isdigit(str[0]))
		return (123);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '$')
			return (56);
		if (str[i] && str[i] == '=' && ((i > 0 && !ft_isalnum(str[i - 1]))))
			return (42);
		i++;
	}
	if (!i)
		return (4645);
	// if (contains_alpha_char || i == 0 || str[i - 1] == '=')
	// return (56);
	return (0);
}

static void ft_print_exported_variables(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static bool ft_set_env_from_arg(char ***env, char *arg)
{
	char *key;
	char *value;
	int equal_pos;

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

#include <stdio.h>

int ft_export(t_subcommand *subcommand, t_token *token, char ***env)
{
	int i;

	i = 1;
	if (!subcommand->args[1])
		return (ft_print_exported_variables(*env), 0);
	if (subcommand->next)
		return (0);
	while (subcommand->args[i])
	{
		fprintf(stderr, ">>> {{%s}}\n", subcommand->args[i]);
		int tmp = ft_check_is_valid_identifier(subcommand->args[i], token->type);
		if (tmp)
		{
			fprintf(stderr, "tmp >>%i\n", tmp);
			ft_putstr_fd(" not a valid identifier\n", 2);
			i++;
			continue ;
		}
		else if (ft_strchr(subcommand->args[i], '='))
		{
			if (!ft_set_env_from_arg(env, subcommand->args[i]))
				return (1);
		}
		else
			*env = ft_env_set(*env, subcommand->args[i], NULL);
		i++;
		token = token->next;
	}
	return (0);
}
