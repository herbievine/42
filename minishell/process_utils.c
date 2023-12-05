/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:04 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 13:02:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "error.h"
#include "str.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

int	ft_handle_in(t_token *token, t_subcommand *subcommand)
{
	int		fd;
	char	*str;

	fd = 0;
	str = NULL;
	if (!token->next && (token->type == TOKEN_LT || token->type == TOKEN_LT_LT))
		return (-1);
	else if (!token->next)
		return (0);
	str = ft_substr(token->next->value, 0, ft_strlen(token->next->value));
	if (!str)
		return (-1);
	if (token->type == TOKEN_LT)
		fd = open(str, O_RDONLY);
	if (token->type == TOKEN_LT_LT)
		fd = subcommand->in_fd;
	if (fd > 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	free(str);
	return (fd);
}

int	ft_handle_out(t_token *token)
{
	char	*str;
	int		fd;

	fd = 0;
	str = NULL;
	if (!token->next && (token->type == TOKEN_GT || token->type == TOKEN_GT_GT))
		return (-1);
	else if (!token->next)
		return (0);
	str = ft_substr(token->next->value, 0, ft_strlen(token->next->value));
	if (!str)
		return (-1);
	if (token->type == TOKEN_GT)
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (token->type == TOKEN_GT_GT)
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (fd > 0)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free(str);
	return (fd);
}

void	ft_open_files(t_command *command,
		t_subcommand *subcommand, int subcommand_nb)
{
	int	fd;
	int	indx;

	fd = 0;
	indx = -1;
	while (++indx < subcommand_nb && command->tokens)
	{
		while (command->tokens && command->tokens->type != TOKEN_PIPE)
			command->tokens = command->tokens->next;
		command->tokens = command->tokens->next;
	}
	while (command->tokens != NULL && command->tokens->type != TOKEN_PIPE)
	{
		fd = ft_handle_in(command->tokens, subcommand);
		if (fd != -1)
			fd = ft_handle_out(command->tokens);
		if (fd == -1)
		{
			ft_error(strerror(errno), (char *)command->tokens->next->value);
			if (command->prev_pipe_fd)
				close(command->prev_pipe_fd);
			return (subcommand->is_executable = false, g_signal = 1, (void)0);
		}
		command->tokens = command->tokens->next;
	}
}

bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
		pid_t *pid, int subcommand_nb)
{
	if (pipe(command->pipe_fd) == PIPE_ERROR)
		return (false);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
			return (close(command->pipe_fd[READ]),
				close(command->pipe_fd[WRITE]), false);
	}
	if (*pid == PID_CHILD)
	{
		if (subcommand_nb != 0)
		{
			dup2(command->prev_pipe_fd, STDIN_FILENO);
			close(command->prev_pipe_fd);
		}
		if (subcommand->next)
			dup2(command->pipe_fd[WRITE], STDOUT_FILENO);
		(close(command->pipe_fd[READ]), close(command->pipe_fd[WRITE]));
		ft_open_files(command, subcommand, subcommand_nb);
	}
	return (true);
}

