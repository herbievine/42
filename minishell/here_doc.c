/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:37:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 18:48:10 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "mem.h"
#include "get_line.h"
#include "str.h"
#include "error.h"
#include "display.h"
#include "expand.h"
#include "signals.h"
#include "lexer_utils.h"
#include "find_in_file.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>

static char	*ft_init_heredoc(t_subcommand *subcommand, t_token *token);
static bool	ft_exit_heredoc(t_subcommand *subcommand, char *buffer);
static bool	ft_heredoc(t_subcommand *subcommand,
				char *limiter, t_token *token);

bool	ft_set_here_doc(t_subcommand *subcommand,
	t_token *token)
{
	char	*limiter;

	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_LT_LT)
		{
			if (!token->next || (token->next->type != TOKEN_SYMBOL
					&& token->next->type != TOKEN_SQ
					&& token->next->type != TOKEN_DQ))
				return (ft_error(ESYN, NULL), g_signal = 1, false);
			limiter = ft_substr(token->next->value, 0,
					token->next->length);
			if (!limiter)
				return (g_signal = 1, false);
			if (subcommand->in_fd > 0)
				close(subcommand->in_fd);
			if (subcommand->is_heredoc)
				unlink(".here_doc_fd");
			if (!ft_heredoc(subcommand, limiter, token))
				return (g_signal = 1, free(limiter), false);
			free(limiter);
		}
		token = token->next;
	}
	return (true);
}

static bool	ft_heredoc_exit_cond(char *line, char *limiter)
{
	if (!line)
		return (ft_putstr_fd("\n", 1), true);
	else if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(line) == ft_strlen(limiter))
		return (free(line), true);
	return (false);
}

static bool	ft_heredoc(t_subcommand *subcommand,
	char *limiter, t_token *token)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_init_heredoc(subcommand, token);
	if (!buffer)
		return (false);
	while (buffer)
	{
		tmp = readline("here> ");
		if (ft_heredoc_exit_cond(tmp, limiter))
			break ;
		line = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = buffer;
		buffer = ft_strjoin(tmp, line);
		(free(tmp), free(line));
	}
	return (ft_exit_heredoc(subcommand, buffer));
}

static char	*ft_init_heredoc(t_subcommand *subcommand, t_token *token)
{
	signal(SIGINT, &ft_handle_nothing);
	signal(SIGQUIT, &ft_handle_nothing);
	token->next->type = TOKEN_EOF;
	subcommand->in_fd = open(".here_doc_fd",
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!subcommand->in_fd)
		return (NULL);
	subcommand->is_heredoc = true;
	return (ft_strdup(""));
}

static bool	ft_exit_heredoc(t_subcommand *subcommand, char *buffer)
{
	int		i;
	char	*tmp;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '$')
		{
			tmp = ft_expand_dollar(subcommand, buffer);
			if (tmp)
				ft_putstr_fd(tmp, subcommand->in_fd);
			free(tmp);
			while (buffer[i] && (ft_is_valid_symbol(buffer[i])))
				i++;
			i--;
		}
		else
			ft_putchar_fd(buffer[i], subcommand->in_fd);
	}
	free(buffer);
	close(subcommand->in_fd);
	subcommand->in_fd = open(".here_doc_fd", O_RDONLY);
	return (true);
}
