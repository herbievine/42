/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:04 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 16:34:47 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
		pid_t *pid, int subcommand_nb)
{
	if (subcommand->next && pipe(command->pipe_fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
		{
			fprintf(stderr, "==%i== close %d\n", getpid(), command->pipe_fd[READ]);
			fprintf(stderr, "==%i== close %d\n", getpid(), command->pipe_fd[WRITE]);
			return (close(command->pipe_fd[READ]),
				close(command->pipe_fd[WRITE]), false);

		}
	}
	if (*pid == PID_CHILD)
	{
		if (subcommand_nb != 0)
		{
			fprintf(stderr, "==%i== dup2 %i, %i\n", getpid(), command->prev_pipe_fd, STDIN_FILENO);
			dup2(command->prev_pipe_fd, STDIN_FILENO);
			fprintf(stderr, "==%i== close %d\n", getpid(), command->prev_pipe_fd);
			close(command->prev_pipe_fd);
		}
		if (subcommand->next)
		{
			fprintf(stderr, "==%i== dup2 %i, %i\n", getpid(), command->pipe_fd[WRITE], STDOUT_FILENO);
			dup2(command->pipe_fd[WRITE], STDOUT_FILENO);
		}
		// else
		// 	dup2(1, STDOUT_FILENO); 
		fprintf(stderr, "==%i== close %d\n", getpid(), command->pipe_fd[READ]);
		close(command->pipe_fd[READ]);
		fprintf(stderr, "==%i== close %d\n", getpid(), command->pipe_fd[WRITE]);
		close(command->pipe_fd[WRITE]);
	}
	return (true);
}

void	ft_redirect(t_subcommand *subcommand)
{
	if (subcommand->in_fd != -1)
	{
		fprintf(stderr, "==%i== dup2 %i, %i\n", getpid(), subcommand->in_fd, STDIN_FILENO);
		dup2(subcommand->in_fd, STDIN_FILENO);
	}
	if (subcommand->out_fd != -1)
	{
		fprintf(stderr, "==%i== dup2 %i, %i\n", getpid(), subcommand->out_fd, STDOUT_FILENO);
		dup2(subcommand->out_fd, STDOUT_FILENO);
	}
}

// fcntl(3, F_GETFD) == -1 ? dprintf(2, " %s: error\n", subcommand->path): dprintf(2, "%s:no error\n", subcommand->path);