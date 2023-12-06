/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:32:38 by codespace         #+#    #+#             */
/*   Updated: 2023/12/06 14:21:17 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../display.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_pwd(t_command *command, t_subcommand *subcommand)
{
	char	*path;

	path = getcwd(NULL, 100);
	ft_print(path, subcommand->out_fd, command->pipe_fd[1]);
	ft_print("\n", subcommand->out_fd, command->pipe_fd[1]);
	free(path);
	return (0);
}
