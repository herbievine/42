/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:37:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/04 13:28:21 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "mem.h"
#include "get_line.h"
#include "str.h"
#include "error.h"
#include "display.h"
#include "expand.h"
#include "lexer_utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	ft_init_here_doc(t_subcommand *subcommand);
static void	ft_print_heredoc(t_subcommand *subcommand, char *line, int fd);
bool		ft_here_doc(t_subcommand *subcommand,
				char *limiter);

bool	ft_set_here_doc(t_subcommand *subcommand,
	t_token *token, int token_length)
{
	char	*path;

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
			if (ft_here_doc(subcommand, path))
				return (true);
			else
				return (false);
		}
		token = token->next;
		token_length--;
	}
	return (true);
}

bool	ft_here_doc(t_subcommand *subcommand, char *limiter)
{
	char	*buffer;

	if (ft_init_here_doc(subcommand) != 0)
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
				ft_print_heredoc(subcommand, buffer, subcommand->in_fd);
			free(buffer);
		}
	}
	close(subcommand->in_fd);
	subcommand->in_fd = open(".here_doc_fd", O_RDONLY);
	return (true);
}

static int	ft_init_here_doc(t_subcommand *subcommand)
{
	int	i;

	i = -1;
	subcommand->in_fd = open(".here_doc_fd",
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!subcommand->in_fd)
		return (-1);
	subcommand->is_heredoc = true;
	write(1, "heredoc>", 9);
	return (0);
}

static	void	ft_print_heredoc(t_subcommand *subcommand, char *line, int fd)
{
	int		i;
	char	*tmp;

	i = -1;
	if (line)
	{
		while (line[++i])
		{
			if (line[i] == '$')
			{
				tmp = ft_expand_dollar(subcommand, line);
				if (tmp)
					ft_putstr_fd(tmp, fd);
				while (line[i] && (ft_is_valid_symbol(line[i])))
					i++;
				i--;
			}
			else
				ft_putchar_fd(line[i], fd);
		}
	}
	write(1, "heredoc>", 9);
}
