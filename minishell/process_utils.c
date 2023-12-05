/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:04 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 15:39:23 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include <unistd.h>

bool	ft_fork_and_pipe(t_subcommand *subcommand,
	int fd[2], pid_t *pid)
{
	if (subcommand->next && pipe(fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
			return (close(fd[READ]), close(fd[WRITE]), false);
	}
	if (*pid == PID_CHILD)
	{
		if (subcommand->in_fd != -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		else
			dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		if (subcommand->out_fd != -1)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
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
