/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 18:50:08 by juliencros       ###   ########.fr       */
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
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>

#define READ 0
#define WRITE 1

int	parent_process(t_command *command, t_subcommand *subcommand, int return_status)
{
	close(command->pipe_fd[WRITE]);
	if (command->prev_pipe_fd != -1)
		close(command->prev_pipe_fd);
	command->prev_pipe_fd = dup(command->pipe_fd[READ]);
	close(command->pipe_fd[READ]);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}

int	ft_spawn_child(t_command *command, t_subcommand *subcommand,
	char ***envp, int subcommand_nb)
{
	int		return_status;

	return_status = 0;
	if (!ft_fork_and_pipe(command, subcommand, &command->pid[subcommand_nb], subcommand_nb))
		return (false);
	if (command->pid[subcommand_nb] == PID_CHILD)
	{
		free(command->pid);
		if (subcommand->builtin && subcommand->is_executable)
			return_status = ft_builtin_valid(command->tokens, subcommand,
					subcommand->path, envp);
		if (!subcommand->is_executable
			|| !subcommand->path || subcommand->builtin)
			(ft_free_all(subcommand, &command->tokens, true), exit(0));
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(subcommand, &command->tokens, false);
		exit(return_status);
	}
	return (parent_process(command, subcommand, return_status));
}

int	ft_multiple_commands(t_command *command, char ***envp)
{
	int				i;
	t_subcommand	*head;
	int				return_status;

	i = 0;
	return_status = 0;
	head = command->subcommands;
	while (head != NULL)
	{
		return_status = ft_spawn_child(command, head, envp, i++);
		head = head->next;
	}
	i = -1;
	while (++i < command->subcommand_length)
		waitpid(command->pid[i], &return_status, 0);
	head = command->subcommands;
	while (head->next != NULL)
		head = head->next;
	close(command->pipe_fd[READ]);
	if (!head->is_executable)
		return (-1);
	if (WIFEXITED(return_status))
		return_status = WEXITSTATUS(return_status);
	return (return_status);
}

int	ft_single_command(t_subcommand *subcommand, t_token **tokens)
{
	pid_t	pid;
	int		return_status;

	pid = fork();
	return_status = 0;
	if (pid == PID_ERROR)
		return (false);
	if (pid == PID_CHILD)
	{
		if (!subcommand->is_executable
			|| !subcommand->path || subcommand->builtin)
			(ft_free_all(subcommand, tokens, true), exit(0));
		ft_redirect(subcommand);
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(subcommand, tokens, false);
		exit(return_status);
	}
	waitpid(pid, &return_status, 0);
	return_status = WEXITSTATUS(return_status);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}

int	ft_execute(t_command *command, char ***envp)
{
	t_subcommand	*head;
	int i = 0;

	head = command->subcommands;
	while (head != NULL)
	{
		head = head->next;
		i++;
	}
	command->subcommand_length = i;
	command->pid = ft_calloc(sizeof(pid_t), command->subcommand_length);
	if (!command->pid)
		return (false);
	if (!command->subcommands->next)
	{
		if (command->subcommands->builtin && command->subcommands->is_executable)
			return (ft_builtin_valid(command->tokens, command->subcommands,
					command->subcommands->path, envp));
		return (ft_single_command(command->subcommands, &command->tokens));
	}
	return (ft_multiple_commands(command, envp));
}
