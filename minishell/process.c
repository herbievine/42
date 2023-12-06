/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/06 15:15:11 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include "str.h"
#include "display.h"
#include "mem.h"
#include "token.h"
#include "error.h"
#include "signals.h"
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
#define ERROE_IS_EXEC 120

int	ft_spawn_child(t_command *command, t_subcommand *subcommand,
		int subcommand_length)
{
	int		return_status;

	return_status = 0;
	if (!ft_fork_and_pipe(command, subcommand,
			&command->pid[subcommand_length], subcommand_length))
		return (false);
	if (command->pid[subcommand_length] == PID_CHILD)
	{
		if (subcommand->builtin && subcommand->is_executable)
		{
			g_signal = ft_builtin_valid(command, subcommand,
					command->tokens, subcommand->path);
			(ft_free_all(command, true), exit(g_signal));
		}
		if (!subcommand->is_executable || !subcommand->path)
			(ft_free_all(command, true), exit(120));
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(command, false);
		exit(return_status);
	}
	return (parent_process(command, subcommand, return_status));
}

int	exec_waitpid(t_command *command)
{
	static int	var;
	int			i;
	int			ret;

	i = -1;
	while (++i < command->subcommand_length)
	{
		waitpid(command->pid[i], &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		if (ret == 131 && !var++)
			ft_putstr_fd("Quit (core dumped)\n", 2);
	}
	return (ret);
}

int	ft_multiple_commands(t_command *command)
{
	int				i;
	t_subcommand	*head;
	int				return_status;

	i = 0;
	return_status = 0;
	head = command->subcommands;
	while (head != NULL)
	{
		return_status = ft_spawn_child(command, head, i++);
		head = head->next;
	}
	return_status = exec_waitpid(command);
	head = command->subcommands;
	while (head->next != NULL)
		head = head->next;
	close(command->pipe_fd[READ]);
	if (head->is_executable == true && return_status == 120)
		g_signal = 1;
	if ((head->is_executable == false || return_status == 120))
		return (-1);
	if (WIFEXITED(return_status))
		return_status = WEXITSTATUS(return_status);
	signal(SIGINT, &ctrlc);
	return (return_status);
}

int	ft_single_command(t_command *command, t_subcommand *subcommand)
{
	pid_t	pid;
	int		return_status;

	pid = fork();
	return_status = 0;
	if (pid == PID_ERROR)
		return (false);
	if (pid == PID_CHILD)
	{
		ft_open_files(command, subcommand, 0, true);
		if (!subcommand->is_executable
			|| !subcommand->path || subcommand->builtin)
			(ft_free_all(command, true), exit(120));
		execve(subcommand->path, subcommand->args, subcommand->envp);
		return_status = ft_define_exit_status(strerror(errno),
				subcommand->path, subcommand->args[0]);
		ft_free_all(command, false);
		exit(return_status);
	}
	waitpid(pid, &return_status, 0);
	if (WIFEXITED(return_status))
		return_status = WEXITSTATUS(return_status);
	if (!subcommand->is_executable || return_status == 120)
		return (-1);
	return (return_status);
}

int	ft_execute(t_command *command)
{
	if (!command->subcommands->next)
	{
		if (command->subcommands->builtin
			&& command->subcommands->is_executable)
		{
			ft_open_files(command, command->subcommands, 0, false);
			if (command->subcommands->is_executable)
				g_signal = ft_builtin_valid(command, command->subcommands,
						command->tokens, command->subcommands->path);
			if (command->subcommands->in_fd != 0)
				close(command->subcommands->in_fd);
			if (command->subcommands->out_fd != 1)
				close(command->subcommands->out_fd);
			return (g_signal);
		}
	}
	return (ft_multiple_commands(command));
}
