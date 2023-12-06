/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:19:55 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 22:32:04 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include <unistd.h>

int	parent_process(t_command *command,
	t_subcommand *subcommand, int return_status)
{
	close(command->pipe_fd[WRITE]);
	if (command->prev_pipe_fd != -1)
		close(command->prev_pipe_fd);
	command->prev_pipe_fd = command->pipe_fd[READ];
	signal(SIGQUIT, SIG_IGN);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}
