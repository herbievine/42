/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:09:48 by codespace         #+#    #+#             */
/*   Updated: 2023/12/06 20:57:09 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../env.h"
#include "../display.h"
#include "../str.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static bool	ft_verify_args(t_subcommand *subcommand)
{
	if (subcommand->args[1] && subcommand->args[2])
	{
		if (!__MACH__)
			ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static char	*ft_find_path(t_command *cmd, t_subcommand *subcommand)
{
	char	*path;

	if (!subcommand->args[1])
		path = ft_env_get_home(*(cmd->env));
	else if (ft_strncmp(subcommand->args[1], "-",
			ft_strlen(subcommand->args[1])) == 0)
	{
		path = ft_env_get(*(cmd->env), "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	}
	else
		path = ft_strdup(subcommand->args[1]);
	return (path);
}

int	ft_cd(t_command *cmd, t_subcommand *subcommand)
{
	char	*path;
	char	*pwd;

	if (!ft_verify_args(subcommand))
		return (1);
	path = ft_find_path(cmd, subcommand);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (free(path), 1);
	}
	free(path);
	pwd = getcwd(NULL, 100);
	if (!pwd)
		return (1);
	path = ft_env_get(*(cmd->env), "PWD");
	if (!path)
		return (1);
	*(cmd->env) = ft_env_set(*(cmd->env), "OLDPWD", path);
	*(cmd->env) = ft_env_set(*(cmd->env), "PWD", pwd);
	return (free(path), free(pwd), 0);
}
