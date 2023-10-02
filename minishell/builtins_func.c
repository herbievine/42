/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:57:39 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/21 17:14:53 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "env.h"
#include "display.h"
#include "str.h"
#include "str2.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int		ft_cd(t_subcommand *subcommand)
{
	char	*path;
	int		ret;

	ret = 0;
	if (!subcommand->args)
		path = ft_get_env("HOME", subcommand);
	else
		path = subcommand->args[0];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ret = 1;
	}
	ft_pwd(subcommand);
	return (ret);
}

int		ft_pwd(t_subcommand *subcommand)
{
	char	*path;

	path = getcwd(NULL, 100);
	ft_putstr_fd(path, subcommand->out_fd);
	ft_putstr_fd("\n", subcommand->out_fd);
	free(path);
	return (0);
}

// int		ft_export(t_subcommand *subcommand)
// {
// 	char **args;
// 	int i;
// 	int j;

// 	args = subcommand->args;
// 	i = 0;
// 	j = 0;
// 	if (!args)
// 		ft_env(subcommand);
// 	if (args && !args[i+1] && ft_strncmp(args[i], "=", 1) != 0)
// 		ft_add_env(args[i], "", subcommand);
// 	while (args && args[i] && ft_strncmp(args[i], "=", 1) != 0)
// 		i++;
// 	while (args && args[i + j])
// 	{
// 		if (ft_strchr(args[i], '='))
// 			ft_add_env(args[i-1], args[i+1], subcommand);
// 		i++;
// 	}
// 	else
// 		ft_putstr_fd("export: not a valid identifier\n", 2);
// 	return (0);
// }

int ft_export(t_subcommand *subcommand)
{
	char **args;
	int i;
	int j;

	args = subcommand->args;
	i = -1;
	j = 0;
	if (!args)
		return (ft_env(subcommand));
	while (args[++i] && ft_strncmp(args[i], "=", 1) != 0)
			ft_add_env(args[i], "", subcommand);
	if (args[i] && ft_strncmp(args[i], "=", 1) == 0 && i == 1 && !args[i++])
		ft_add_env(args[i], args[i], subcommand);
	if (args[i+1])
		ft_putstr_fd("export: bad assignment\n", 2);
	return (0);
	
}

int		ft_unset(t_subcommand *subcommand)
{
	char **args;
	int i;

	args = subcommand->args;
	i = 0;
	while (args[i])
	{
		ft_remove_env(args[i], subcommand);
		i++;
	}
	return (0);
}

int		ft_env(t_subcommand *subcommand)
{
	int		i;

	i = 0;
	while (global_env[i])
	{
		ft_putstr_fd(global_env[i], subcommand->out_fd);
		ft_putstr_fd("\n", subcommand->out_fd);
		i++;
	}
	return (0);
}

int		ft_exit(t_subcommand *subcommand)
{
	int		i;

	i = 0;
	if (subcommand->args)
		i = ft_atoi(subcommand->args[0]);
	exit(i);
	return (0);
}
