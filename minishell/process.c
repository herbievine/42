/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/28 18:00:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include "str.h"
#include "mem.h"
#include "str2.h"
#include "token.h"
#include "error.h"

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
		if (idx == 0 && subcommand->in_fd != -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		if (!subcommand->next)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (true);
}

bool	ft_spawn_child(t_subcommand *subcommand, t_token **tokens, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (!ft_fork_and_pipe(subcommand, fd, &pid, idx))
		return (false);
	if (pid == PID_CHILD)
	{
		if (subcommand->path)
			execve(subcommand->path, subcommand->args, subcommand->envp);
		else
			dprintf(2, M "%s: " ECNF "\n", subcommand->args[0]);
		ft_free_subcommands(subcommand);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (true);
}

bool	ft_exec_cmds(t_subcommand *subcommand, t_token **tokens)
{
	int				i;
	t_subcommand	*head;

	i = -1;
	head = subcommand;
	while (++i >= 0 && head != NULL)
	{
		if (!ft_spawn_child(head, tokens, i))
			return (false);
		head = head->next;
	}

	while (i-- > 0)
		wait(NULL);
	return (true);
}
