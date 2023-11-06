/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/06 11:02:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include "str.h"
#include "mem.h"
#include "str2.h"
#include "token.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

bool	ft_fork_and_pipe(t_subcommand *subcommand,
	int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		close(fd[0]);
		close(fd[1]);
		return (false);
	}
	if (*pid == PID_CHILD)
	{
		if (idx == 0 && subcommand->in_fd == -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		dprintf(2, "closing fd[0] in child: %d\n", fd[0]);
		close(fd[0]);
		if (!subcommand->next)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		dprintf(2, "closing fd[1] in child: %d\n", fd[1]);
		close(fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dprintf(2, "closing fd[0] in parent: %d\n", fd[0]);
		close(fd[0]);
		dprintf(2, "closing fd[1] in parent: %d\n", fd[1]);
		close(fd[1]);
	}
	return (true);
}

bool	ft_spawn_child(t_subcommand *subcommand, t_token **tokens,
	int idx)
{
	pid_t	pid;
	int		fd[2];

	if (!ft_fork_and_pipe(subcommand, fd, &pid, idx))
		return (false);
	if (pid == PID_CHILD)
	{
		execve(subcommand->path, subcommand->args, subcommand->envp);
		ft_free_subcommands(subcommand);
	}
	dprintf(2, "waitpid: %d\n", waitpid(pid, NULL, 0));
	return (true);
}

bool	ft_single_command(t_subcommand *subcommand)
{
	pid_t	pid;

	pid = fork();
	if (pid == PID_ERROR)
		return (false);
	if (pid == PID_CHILD)
		execve(subcommand->path, subcommand->args, subcommand->envp);
	waitpid(pid, NULL, 0);
	return (true);
}

bool	ft_multiple_commands(t_subcommand *subcommand, t_token **tokens)
{
	int				i;
	t_subcommand	*head;

	i = 0;
	head = subcommand;
	while (head != NULL)
	{
		if (!ft_spawn_child(head, tokens, i))
			return (false);
		head = head->next;
		i++;
	}
	return (true);
}

bool	ft_execute(t_subcommand *subcommand, t_token **tokens)
{
	if (subcommand->next)
		return (ft_multiple_commands(subcommand, tokens));
	else
		return (ft_single_command(subcommand));
}
