/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:04 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 21:27:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
		pid_t *pid, int subcommand_length)
{
	if (pipe(command->pipe_fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
			return (close(command->pipe_fd[READ]),
				close(command->pipe_fd[WRITE]), false);
	}
	if (*pid == PID_CHILD)
	{
		if (subcommand_length != 0 && subcommand->in_fd == -1)
		{
			dup2(command->prev_pipe_fd, STDIN_FILENO);
			close(command->prev_pipe_fd);
		}
		else if (subcommand->in_fd != -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		if (subcommand->next && subcommand->out_fd == -1)
			dup2(command->pipe_fd[WRITE], STDOUT_FILENO);
		else if (subcommand->out_fd != -1)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		(close(command->pipe_fd[READ]), close(command->pipe_fd[WRITE]));
	}
	return (true);
}

void	ft_redirect(t_subcommand *subcommand)
{
	if (subcommand->in_fd != -1)
		dup2(subcommand->in_fd, STDIN_FILENO);
	if (subcommand->out_fd != -1)
		dup2(subcommand->out_fd, STDOUT_FILENO);
}
