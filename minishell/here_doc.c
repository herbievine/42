/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:37:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/06 20:19:23 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "mem.h"
#include "str.h"
#include "error.h"
#include "display.h"
#include "expand.h"
#include "signals.h"
#include "lexer_utils.h"
#include "expand.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>

static char	*ft_init_heredoc(t_subcommand *subcommand,
				t_token *token, int here_doc_indx);
static bool	ft_exit_heredoc(t_subcommand *subcommand, char *buffer);
static bool	ft_heredoc(t_subcommand *subcommand, char *limiter,
				t_token *token, int here_doc_indx);

bool	ft_set_here_doc(t_subcommand *subcommand,
	t_token *token)
{
	char	*limiter;
	int		here_doc_indx;

	here_doc_indx = 0;
	while (token)
	{
		if (token && token->type == TOKEN_LT_LT)
		{
			if (!token->next || (token->next->type != TOKEN_SYMBOL
					&& token->next->type != TOKEN_SQ
					&& token->next->type != TOKEN_DQ
					&& token->next->type != TOKEN_EOF))
				return (ft_error(ESYN, NULL), g_signal = 1, false);
			limiter = ft_substr(token->next->value, 0, token->next->length);
			if (!limiter)
				return (g_signal = 1, false);
			if (!ft_heredoc(subcommand, limiter, token, here_doc_indx))
				return (g_signal = 1, free(limiter), false);
			(free(limiter), here_doc_indx++);
		}
		token = token->next;
		if (token && token->type == TOKEN_PIPE && subcommand)
			subcommand = subcommand->next;
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
	char *limiter, t_token *token, int here_doc_indx)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	if (subcommand->in_fd > 0)
		close(subcommand->in_fd);
	if (subcommand->is_heredoc)
		unlink(subcommand->heredoc_name);
	free(subcommand->heredoc_name);
	buffer = ft_init_heredoc(subcommand, token, here_doc_indx);
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

static char	*ft_init_heredoc(t_subcommand *subcommand,
			t_token *token, int here_doc_indx)
{
	char	*tmp;

	token->next->type = TOKEN_EOF;
	tmp = ft_itoa(here_doc_indx);
	if (!tmp)
		return (NULL);
	subcommand->heredoc_name = ft_strjoin(".here_doc", tmp);
	free(tmp);
	if (!subcommand->heredoc_name)
		return (NULL);
	subcommand->in_fd = open(subcommand->heredoc_name,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (subcommand->in_fd == -1)
		return (NULL);
	subcommand->is_heredoc = true;
	return (ft_strdup(""));
}

static bool	ft_exit_heredoc(t_subcommand *subcommand, char *buffer)
{
	char	*tmp;

	tmp = ft_iter_in_string(subcommand, buffer);
	if (!tmp)
		return (false);
	ft_putstr_fd(tmp, subcommand->in_fd);
	free(tmp);
	close(subcommand->in_fd);
	return (true);
}
