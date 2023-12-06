/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:59:10 by codespace         #+#    #+#             */
/*   Updated: 2023/12/06 14:26:42 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../display.h"

int	ft_env(t_command *command, t_subcommand *subcommand, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_print(env[i], subcommand->out_fd, command->pipe_fd[1]);
		ft_print("\n", subcommand->out_fd, command->pipe_fd[1]);
		i++;
	}
	return (0);
}
