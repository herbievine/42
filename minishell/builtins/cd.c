/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:09:48 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 10:09:48 by codespace        ###   ########.fr       */
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
	if (subcommand->args[2])
	{
		if (!__MACH__)
			ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static char	*ft_find_path(t_subcommand *subcommand)
{
	char	*path;

	if (!subcommand->args[1])
		return (ft_env_get_home(subcommand->envp));
	else if (ft_strncmp(subcommand->args[1], "-",
			ft_strlen(subcommand->args[1])) == 0)
	{
		path = ft_env_get(subcommand->envp, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	}
	else
		path = subcommand->args[1];
	return (path);
}

int	ft_cd(t_subcommand *subcommand)
{
	char	*path;

	if (!ft_verify_args(subcommand))
		return (1);
	path = ft_find_path(subcommand);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	subcommand->envp = ft_env_set(subcommand->envp, "OLDPWD",
			ft_env_get(subcommand->envp, "PWD"));
	subcommand->envp = ft_env_set(subcommand->envp,
			"PWD", getcwd(NULL, 100));
	return (0);
}
