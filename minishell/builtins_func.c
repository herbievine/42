/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:57:39 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 18:07:30 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "env.h"
#include "display.h"
#include "str.h"
#include "builtins_func_utils.h"
#include "signals.h"
#include "token.h"
#include "error.h"
#include "free.h"
#include "history.h"
#include "find_cmds.h"
#include "char.h"
#include "expand.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int	ft_cd(t_subcommand *subcommand)
{
	char	*path;

	if (!subcommand->args[1])
	{
		path = ft_env_get(subcommand->envp, "HOME");
		if (!path)
		{
			path = ft_strjoin("/Users/", ft_env_get(subcommand->envp, "USER"));
			return (chdir(path), free(path), 0);
		}
		else
			return (chdir(path), 0);
	}
	else if (subcommand->args[2])
		return (0);
	if (ft_strncmp(subcommand->args[1], "-",
			ft_strlen(subcommand->args[1])) == 0)
	{
		path = ft_env_get(subcommand->envp, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	}
	if (subcommand->args[1][0] == '$')
		path = ft_expand_dollar(subcommand, subcommand->args[1]);
	else
		path = subcommand->args[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	else
	{
		subcommand->envp = ft_env_set(subcommand->envp, "OLDPWD",
			ft_env_get(subcommand->envp, "PWD"));
		subcommand->envp = ft_env_set(subcommand->envp, "PWD", getcwd(NULL, 100));
	}
	return (0);
}

void	ft_pwd(t_subcommand *subcommand)
{
	char	*path;

	path = getcwd(NULL, 100);
	ft_putstr_fd(path, subcommand->out_fd);
	ft_putstr_fd("\n", subcommand->out_fd);
	free(path);
	return ;
}

/**
 * @brief The env utility shall obtain the current environment, 
 * the second argument is to write the normed export format or not
 * 
 * @param envp 
 * @param is_export 
 * @return int 
 */
int	ft_env(char **env, int is_export)
{
	int	i;

	printf("env\n");
	i = 0;
	while (env[i])
	{
		if (is_export)
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_subcommand *subcommand, char ***envp, t_token *tokens)
{
	int	i;
	int	exit_value;

	i = -1;
	exit_value = 0;
	if (subcommand->args[1])
	{
		exit_value = ft_check_digit(subcommand->args[1]);
		if (subcommand->args[1] && subcommand->args[2] && !exit_value)
			return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
		if (!exit_value && subcommand->args[1])
			exit_value = ft_atoi(subcommand->args[1]);
	}
	ft_clear_tokens(&tokens);
	ft_free_array(*envp, -1);
	ft_free_subcommands(subcommand);
	ft_history_clear();
	exit(exit_value % 256);
}
