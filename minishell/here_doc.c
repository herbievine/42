/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:37:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/21 19:54:44 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "mem.h"
#include "get_line.h"
#include "str.h"
#include "str2.h"
#include "error.h"
#include "display.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	ft_init_here_doc(t_subcommand *subcommand, int is_pipe);
static void	ft_print_heredoc(char *line, int fd, int is_pipe);
bool		ft_here_doc(t_subcommand *subcommand,
				char *limiter, int is_pipe);
int			ft_find_pipe(t_token *token);

bool	ft_set_here_doc(t_subcommand *subcommand,
	t_token *token, int token_length)
{
	char	*path;
	int		is_pipe;

	is_pipe = ft_find_pipe(token);
	while (token && token_length > 0)
	{
		if (token->type == TOKEN_LT_LT)
		{
			if (!token->next)
				return (printf(M""ESYN" `newline'\n"), false);
			if (token->next->type != TOKEN_SYMBOL)
				return (printf(M""ESYN" `%s'\n", token->next->value), false);
			path = (char *)token->next->value;
			path[token->next->length] = '\0';
			token->next->type = TOKEN_EOF;
			if (ft_here_doc(subcommand, path, is_pipe))
				return (true);
			else
				return (false);
		}
		token = token->next;
		token_length--;
	}
	return (true);
}

bool	ft_here_doc(t_subcommand *subcommand, char *limiter, int is_pipe)
{
	char	*buffer;

	if (ft_init_here_doc(subcommand, is_pipe) != 0)
		return (false);
	while (subcommand->in_fd > 0)
	{
		buffer = ft_calloc(10000, sizeof(char *));
		if (!buffer)
			return (false);
		if (ft_get_line(buffer, '\n', 1))
		{
			if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
				&& ft_strlen(buffer) == ft_strlen(limiter) + 1)
			{
				free(buffer);
				break ;
			}
			else
				ft_print_heredoc(buffer, subcommand->in_fd, is_pipe);
			free(buffer);
		}
	}
	close(subcommand->in_fd);
	subcommand->in_fd = open(".here_doc_fd", O_RDONLY);
	return (true);
}

static int	ft_init_here_doc(t_subcommand *subcommand, int is_pipe)
{
	int	i;

	i = -1;
	subcommand->in_fd = open(".here_doc_fd",
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!subcommand->in_fd)
		return (-1);
	subcommand->is_heredoc = true;
	while (++i < is_pipe)
		write (1, "pipe ", 5);
	write(1, "heredoc>", 9);
	return (0);
}

static	void	ft_print_heredoc(char *line, int fd, int is_pipe)
{
	int	i;

	i = -1;
	if (line)
		ft_putstr_fd(line, fd);
	while (++i < is_pipe)
		write(1, "pipe ", 5);
	write(1, "heredoc>", 9);
}

int	ft_find_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			i++;
		token = token->next;
	}
	return (i);
}
