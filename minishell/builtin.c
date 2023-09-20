/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:02 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/19 12:08:29 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "str.h"
#include "str2.h"
#include "builtins_func.h"
#include "echo.h"
#include  <stdio.h>



bool	ft_builtin(t_subcommand *subcommand, t_token *token)
{
	t_builtin	*builtin;
	char 		*path;

	path = (char *)token->value;
	path[token->length] = '\0';
	if (ft_if_builtin(path))
		return (ft_builtin_valid(token, subcommand, path), true);
	return (false);
}

bool	ft_if_builtin(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4) ||
	(ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2) ||
	(ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3) ||
	(ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6) ||
	(ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5) ||
	(ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3) ||
	(ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4))
		return (true);
	return (false);
}

bool	ft_builtin_valid(t_token *token, t_subcommand *subcommand, char *cmd)
{
	
	if (ft_strncmp(cmd, "echo", 4) == 0 && token->next)
		return (ft_echo(token->next, subcommand), true);
	if (ft_strncmp(cmd, "cd", 2) == 0 && token->next && !token->next->next)
		return (ft_cd(subcommand), true);
	if (ft_strncmp(cmd, "pwd", 3) == 0 && !token->next)
		return (ft_pwd(subcommand), true);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (ft_export(subcommand), true);
	if (ft_strncmp(cmd, "unset", 5) == 0 && token->next && !token->next->next)
		return (ft_unset(subcommand), true);
	if (ft_strncmp(cmd, "env", 3) == 0	)
		return (ft_env(subcommand), true);
	if (ft_strncmp(cmd, "exit", 4) == 0 && token->next && !token->next->next || !token->next)
		return (ft_exit(subcommand), true);
	return (false);
}