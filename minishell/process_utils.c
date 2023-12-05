/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:30:04 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 20:23:12 by jcros            ###   ########.fr       */
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
		fd = open(".here_doc_fd", O_RDONLY);
	if ((fd == -1 || fd > 0) && subcommand->in_fd >= 0)
		close(subcommand->in_fd);
	if (fd > 0)
	{
		subcommand->in_fd = fd;
		(dup2(fd, STDIN_FILENO), close(fd));
	}
	free(str);
	return (fd);
}

int	ft_handle_out(t_token *token, t_subcommand *subcommand)
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
	if ((fd == -1 || fd > 0) && subcommand->out_fd >= 0)
		close(subcommand->out_fd);
	if (fd > 0)
	{
		subcommand->out_fd = fd;
		(dup2(fd, STDOUT_FILENO), close(fd));
	}
	free(str);
	return (fd);
}

static int	ft_handle_io(t_command *cmd, t_token *curr, t_subcommand *sub)
{
	int	fd;

	fd = ft_handle_in(curr, sub);
	if (fd != -1)
		fd = ft_handle_out(curr, sub);
	if (fd == -1)
	{
		ft_error(strerror(errno), (char *)curr->next->value);
		if (cmd->prev_pipe_fd > 0)
			close(cmd->prev_pipe_fd);
		sub->is_executable = false;
		g_signal = 1;
	}
	return (fd);
}

void	ft_open_files(t_command *command,
		t_subcommand *subcommand, int subcommand_nb)
{
	int			i;
	t_token		*token_head;

	i = -1;
	token_head = command->tokens;
	while (++i < subcommand_nb && token_head)
	{
		while (token_head && token_head->type != TOKEN_PIPE)
			token_head = token_head->next;
		token_head = token_head->next;
	}
	while (token_head != NULL && token_head->type != TOKEN_PIPE)
	{
		ft_handle_io(command, token_head, subcommand);
		token_head = token_head->next;
	}
}

bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
		pid_t *pid, int subcommand_length)
{
	if (pipe(command->pipe_fd) == PIPE_ERROR)
		return (false);
	signal(SIGINT, SIG_IGN);
	*pid = fork();
	if (*pid == PID_ERROR)
	{
		if (subcommand->next)
			return (close(command->pipe_fd[READ]),
				close(command->pipe_fd[WRITE]), false);
	}
	if (*pid == PID_CHILD)
	{
		signal(SIGINT, &ctrlc);
		signal(SIGQUIT, &antislash);
		if (subcommand_length != 0)
		{
			dup2(command->prev_pipe_fd, STDIN_FILENO);
			close(command->prev_pipe_fd);
		}
		if (subcommand->next)
			dup2(command->pipe_fd[WRITE], STDOUT_FILENO);
		(close(command->pipe_fd[READ]), close(command->pipe_fd[WRITE]));
		ft_open_files(command, subcommand, subcommand_length);
	}
	return (true);
}
