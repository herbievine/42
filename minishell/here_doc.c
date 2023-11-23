/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:37:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/23 11:02:26 by juliencros       ###   ########.fr       */
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
#include "find_in_file.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	ft_init_here_doc(t_subcommand *subcommand);
static void	ft_print_heredoc(t_subcommand *subcommand, char *line, int fd);
bool		ft_here_doc(t_subcommand *subcommand,
				char *limiter);

bool	ft_set_here_doc(t_subcommand *subcommand,
	t_token *token)
{
	char	*path;

	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_LT_LT)
		{
			if (!token->next || (token->next->type != TOKEN_SYMBOL
					&& token->next->type != TOKEN_SQ
					&& token->next->type != TOKEN_DQ))
				return (ft_error(ESYN, NULL), g_signal = 1, false);
			path = ft_substr(token->next->value, 0,
					token->next->length);
			if (!path)
				return (g_signal = 1, false);
			token->next->type = TOKEN_EOF;
			if (subcommand->in_fd > 0)
				close(subcommand->in_fd);
			if (subcommand->is_heredoc)
				unlink(".here_doc_fd");
			if (!ft_here_doc(subcommand, path))
				return (g_signal = 1, false);
		}
		token = token->next;
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
			return (ft_putstr_fd("\n", 1), false);
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
