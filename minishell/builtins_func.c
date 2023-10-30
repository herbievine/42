/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:57:39 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/28 13:14:44 by codespace        ###   ########.fr       */
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
	if (!subcommand->args[1])
		path = ft_get_cpy_env(subcommand, "HOME");
	else
		path = subcommand->args[1];
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

int ft_export(t_subcommand *subcommand)
{
	int		i;
	int		j;
	char	*str;

	i = 1;
	j = 0;
	if (!subcommand->args[1])
		return (ft_env(subcommand));
	while (subcommand->args[i] && subcommand->args[i][j])
	{
		if (ft_strchr(subcommand->args[i], '='))
		{
			str = ft_substr(subcommand->args[i], 0, ft_position(subcommand->args[i], '='));
			printf("str = %s\n", str);
		 	ft_add_cpy_env_var(subcommand, str);
			free(str);
		}
		else
			ft_add_cpy_env_var(subcommand, subcommand->args[i]);
		i++;
	}
	if (i == 2 && ft_strchr(subcommand->args[i - 1], '='))
		ft_add_cpy_env_var(subcommand, subcommand->args[i-1]);
	if (subcommand->args[i])
		ft_putstr_fd("export: bad assignment\n", 2);
	i = 0;
	while (subcommand->cpy_envp[i])
		i++;
	printf("i = %d\n", i);
	
	return (0);
}

int		ft_unset(t_subcommand *subcommand)
{
	char	**args;
	
	args = subcommand->args;
	if (args[1])
		ft_remove_cpy_env_var(subcommand->cpy_envp, args[1]);
	return (0);
}

int		ft_env(t_subcommand *subcommand)
{
	int		i;

	i = 0;
	while (subcommand->cpy_envp[i])
	{
		ft_putstr_fd(subcommand->cpy_envp[i], subcommand->out_fd);
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
