/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/07 18:47:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include "str.h"
#include "mem.h"
#include "token.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

#define READ 0
#define WRITE 1

bool	ft_fork_and_pipe(t_subcommand *subcommand,
	int fd[2], pid_t *pid, int idx)
{
	if (subcommand->next && pipe(fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
		{
			close(fd[READ]);
			close(fd[WRITE]);
		}
		return (false);
	}
	if (*pid == PID_CHILD)
	{
		if (idx == 0 && subcommand->in_fd != -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		else
			dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		if (!subcommand->next && subcommand->out_fd != -1)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		else
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
	}
	else
		close(fd[WRITE]);
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
		dprintf(2, "execve: %s\n", subcommand->path);
		execve(subcommand->path, subcommand->args, subcommand->envp);
		ft_free_subcommands(subcommand);
		perror("execve");
		exit(1);
	}
	else 
		close(fd[READ]);
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
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
	return (true);
}

bool	ft_execute(t_subcommand *subcommand, t_token **tokens)
{
	if (!subcommand->next)
		return (ft_single_command(subcommand));
	return (ft_multiple_commands(subcommand, tokens));
}
