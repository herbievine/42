/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 12:33:06 by codespace        ###   ########.fr       */
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

int	parent_process(t_command *command,
	t_subcommand *subcommand, int return_status)
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
	if (!ft_fork_and_pipe(command, subcommand,
			&command->pid[subcommand_nb], subcommand_nb))
		return (false);
	if (command->pid[subcommand_nb] == PID_CHILD)
	{
		if (subcommand->builtin && subcommand->is_executable)
			return_status = ft_builtin_valid(command->tokens, subcommand,
					subcommand->path, envp);
		if (!subcommand->is_executable
			|| !subcommand->path || subcommand->builtin)
			(ft_free_all(command, subcommand, &command->tokens, true), exit(0));
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(command, subcommand, &command->tokens, false);
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

int	ft_single_command(t_command *command,
	t_subcommand *subcommand, t_token **tokens)
{
	int		return_status;

	command->pid[0] = fork();
	return_status = 0;
	if (command->pid[0] == PID_ERROR)
		return (false);
	if (command->pid[0] == PID_CHILD)
	{
		ft_open_files(command, subcommand, 0);
		if (!subcommand->is_executable
			|| !subcommand->path || subcommand->builtin)
			(ft_free_all(command, subcommand, tokens, true), exit(0));
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(command, subcommand, tokens, false);
		exit(return_status);
	}
	waitpid(command->pid[0], &return_status, 0);
	return_status = WEXITSTATUS(return_status);
	if (!subcommand->is_executable)
		return (-1);
	return (return_status);
}

int	ft_execute(t_command *command, char ***envp)
{
	if (!command->subcommands->next)
	{
		if (command->subcommands->builtin
			&& command->subcommands->is_executable)
			return (ft_builtin_valid(command->tokens, command->subcommands,
					command->subcommands->path, envp));
		return (ft_single_command(command,
				command->subcommands, &command->tokens));
	}
	return (ft_multiple_commands(command, envp));
}
