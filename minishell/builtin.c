/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:02 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/26 17:59:54 by codespace        ###   ########.fr       */
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
	if (subcommand->out_fd == -1)
		subcommand->out_fd = 1;
	if (ft_strncmp(cmd, "echo", 4) == 0 && token->next)
		ft_echo(token->next, subcommand);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && token->next && !token->next->next)
		ft_cd(subcommand);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && !token->next)
		ft_pwd(subcommand);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(subcommand);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && token->next && !token->next->next)
		ft_unset(subcommand);
	else if (ft_strncmp(cmd, "env", 3) == 0	)
		ft_env(subcommand);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && token->next && !token->next->next || !token->next)
		ft_exit(subcommand);
	subcommand->out_fd = -1;
	return (true);
}