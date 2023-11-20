/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/20 11:35:23 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include "str.h"
#include "mem.h"
#include "token.h"
#include "error.h"
#include "exit.h"
#include "builtin.h"
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

int	ft_spawn_child(t_subcommand *subcommand, t_token **tokens, char ***envp)
{
	pid_t	pid;
	int		return_status;
	int		fd[2];

	return_status = 0;
	if (!ft_fork_and_pipe(subcommand, fd, &pid))
		return (false);
	if (pid == PID_CHILD)
	{
		close(fd[READ]);
		if (ft_if_builtin(subcommand->path) && subcommand->is_executable)
			return_status = ft_builtin_valid(*tokens, subcommand,
					subcommand->path, envp);
		if (!subcommand->is_executable || !subcommand->path || subcommand->builtin)
			exit(0);
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_subcommands(subcommand);
		ft_clear_tokens(tokens);
		exit(return_status);
	}
	close(fd[WRITE]);
	if (subcommand->next && subcommand->next->in_fd == -1)
		subcommand->next->in_fd = fd[READ];
	else 
		close(fd[READ]);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}

int	ft_single_command(t_subcommand *subcommand, t_token **tokens, char ***envp)
{
	pid_t	pid;
	int		return_status;

	if (ft_if_builtin(subcommand->path) && subcommand->is_executable)
		return (return_status = ft_builtin_valid(*tokens, subcommand,
				subcommand->path, envp));
	pid = fork();
	return_status = 0;
	if (pid == PID_ERROR)
		return (false);
	if (pid == PID_CHILD)
	{
		if (!subcommand->is_executable || !subcommand->path || subcommand->builtin)
			exit(0);
		ft_redirect(subcommand);
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_subcommands(subcommand);
		ft_clear_tokens(tokens);
		exit(return_status);
	}
	waitpid(pid, &return_status, 0);
	return_status = WEXITSTATUS(return_status);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}

int	ft_multiple_commands(t_subcommand *subcommand,
	t_token **tokens, char ***envp)
{
	int				i;
	t_subcommand	*head;
	int				return_status;

	i = 0;
	return_status = 0;
	head = subcommand;
	while (head != NULL)
	{
		return_status = ft_spawn_child(head, tokens, envp);
		head = head->next;
		i++;
	}
	while (i--)
		waitpid(-1, &return_status, 0);
	while (subcommand->next != NULL)
		subcommand = subcommand->next;
	if (!subcommand->is_executable)
		return (-1);
	return_status = WEXITSTATUS(return_status);
	return (return_status);
}

int	ft_execute(t_subcommand *subcommand, t_token **tokens, char ***envp)
{
	if (!subcommand->next)
		return (ft_single_command(subcommand, tokens, envp));
	return (ft_multiple_commands(subcommand, tokens, envp));
}
