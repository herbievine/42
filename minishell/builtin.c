/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:02 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 20:13:25 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "str.h"
#include "builtins/builtins.h"
#include <stdio.h>

bool	ft_builtin(t_command *command, t_subcommand *subcommand,
			t_token *token)
{
	char		*path;

	path = (char *)token->value;
	path[token->length] = '\0';
	if (ft_if_builtin(path))
		return (ft_builtin_valid(command, subcommand, token, path), true);
	return (false);
}

bool	ft_if_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	if ((ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		|| (ft_strncmp(cmd, "/bin/echo", 9) == 0 && ft_strlen(cmd) == 9)
		|| (ft_strncmp(cmd, "/usr/bin/echo", 13) == 0 && ft_strlen(cmd) == 13)
		|| (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		|| (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		|| (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		|| (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		|| (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		|| (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4))
		return (true);
	return (false);
}

int	ft_builtin_valid(t_command *command, t_subcommand *subcommand,
			t_token *token, char *cmd)
{
	if (subcommand->out_fd == -1)
		subcommand->out_fd = 1;
	if (ft_strschr(cmd, "echo") == 0)
		return (ft_echo(subcommand));
	else if (ft_strschr(cmd, "cd") == 0)
		return (ft_cd(subcommand));
	else if (ft_strschr(cmd, "pwd") == 0)
		return (ft_pwd(subcommand));
	else if (ft_strschr(cmd, "export") == 0)
		return (ft_export(command, subcommand, token->next));
	else if (ft_strschr(cmd, "unset") == 0)
		return (ft_unset(command, subcommand));
	else if (ft_strschr(cmd, "env") == 0)
		return (ft_env(*(command->env)));
	else if (ft_strschr(cmd, "exit") == 0)
		return (ft_exit(subcommand, command));
	subcommand->out_fd = -1;
	return (1);
}
