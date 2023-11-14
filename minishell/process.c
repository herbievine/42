/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/13 13:39:57 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include "str.h"
#include "mem.h"
#include "token.h"
#include "error.h"
#include "exit.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

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

int	ft_spawn_child(t_subcommand *subcommand, t_token **tokens,
	int idx)
{
	pid_t	pid;
	int		return_status;
	int		fd[2];

	return_status = 0;
	if (!ft_fork_and_pipe(subcommand, fd, &pid, idx))
		return (false);
	if (pid == PID_CHILD)
	{
		close(fd[READ]);
		if (!subcommand->is_executable || !subcommand->path)
			exit(1);
		execve(subcommand->path, subcommand->args, subcommand->cpy_envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path);
		dprintf(2, "minishell: %s: %s\n", subcommand->path, strerror(errno));
		ft_free_subcommands(subcommand);
		ft_clear_tokens(tokens);
		exit(1);
	}
	else 
	{
		// waitpid(pid, &return_status, 0);
		close(fd[WRITE]);
		if (subcommand->next)
			subcommand->next->in_fd = fd[READ];
		if (subcommand->next)
			return_status = ft_spawn_child(subcommand->next, tokens, idx + 1);
		else 
			close(fd[READ]);
	}
	return (return_status);
}

int	ft_single_command(t_subcommand *subcommand, t_token **tokens)
{
	pid_t	pid;
	int		return_status;

	char *args[] = {"cat", "Make\"file\"", NULL};

	pid = fork();
	return_status = 0;
	if (pid == PID_ERROR)
		return (false);
	if (pid == PID_CHILD)
	{
		if (!subcommand->is_executable || !subcommand->path)
			exit(1);
		if (subcommand->in_fd != -1)
			dup2(subcommand->in_fd, STDIN_FILENO);
		if (subcommand->out_fd != -1)
			dup2(subcommand->out_fd, STDOUT_FILENO);
		execve(subcommand->path, subcommand->args, subcommand->cpy_envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path);
		dprintf(2, "minishell: %s: %s\n", subcommand->path, strerror(errno));
		ft_free_subcommands(subcommand);
		ft_clear_tokens(tokens);
		exit(1);
	}
	waitpid(pid, &return_status, 0);
	return (return_status);
}

int	ft_multiple_commands(t_subcommand *subcommand, t_token **tokens)
{
	int				i;
	t_subcommand	*head;
	int				return_status;

	i = 0;
	return_status = 0;
	head = subcommand;
	while (head->next != NULL)
	{
		i++;
		head = head->next;
	}
	head = subcommand;
	return (ft_spawn_child(head, tokens, i));
}

int	ft_execute(t_subcommand *subcommand, t_token **tokens)
{
	int	i;
	t_subcommand *head;
	int return_status;

	i = 0;
	head = subcommand;
	while (head)
	{
		if (head->is_executable)
			i++;
		head = head->next;
	}
	if (!subcommand->next)
		return (ft_single_command(subcommand, tokens));
	return_status = ft_multiple_commands(subcommand, tokens);
	while (i--)
		wait(NULL);
	return (return_status);
}
