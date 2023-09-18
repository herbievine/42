/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/21 18:04:10 by juliencros       ###   ########.fr       */
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

bool	pipe_and_execute(t_subcommand *subcommand, int i);
void ft_free_fd(int fd[2], t_subcommand *subcommand);

bool	ft_fork_and_pipe(t_subcommand *subcommand, int fd[2], pid_t *pid, int i)
{
	if (pipe(fd) == -1)
		return (false);
	*pid = fork();
	if (*pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (false);
	}
	if (*pid == 0)
	{
		if (i == 0 || subcommand->in_fd != 0)
			dup2(subcommand->in_fd, STDIN_FILENO);
		if (!subcommand->next || subcommand->out_fd != 1)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (true);
}

bool	pipe_and_execute(t_subcommand *subcommand, int i)
{
	pid_t	pid;
	int		fd[2];
	int		indx = -1;

	if (!ft_fork_and_pipe(subcommand, fd, &pid, i))
		return (false);
	if (pid == 0)
	{
		if (subcommand->path)
			execve(subcommand->path, subcommand->args, NULL);
		ft_free_fd(fd, subcommand);
		exit(0);
	}
	else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, &indx, 0);
		}
	return (true);
}

bool	execution(t_subcommand *subcommand)
{
	int				i;
	int				j;
	t_subcommand	*tmp;

	i = 0;
	j = -1;

	while (subcommand != NULL)
	{
		pipe_and_execute(subcommand, i);
		subcommand = subcommand->next;
		i++;
	}
	while (++j < i)
		wait(NULL);
	return (true);
}

void ft_free_fd(int fd[2], t_subcommand *subcommand)
{
	int i;

	i = 0;
	while (i < 3)
		close(i++);
	ft_free_subcommands(subcommand);
}