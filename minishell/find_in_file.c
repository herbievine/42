/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/17 15:43:04 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_in_file.h"
#include <stdio.h>
#include "error.h"
#include "str.h"
#include "parse.h"
#include "display.h"
#include <unistd.h>
#include <fcntl.h>

static void ft_print_error(char *error)
{
	ft_putstr_fd(M, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	ft_close_in_files(t_subcommand *subcommand)
{
	if (subcommand->in_fd > 0)
		close(subcommand->in_fd);
	if (subcommand->is_heredoc)
		unlink(".here_doc_fd");
}

bool	ft_set_in_fd(t_subcommand *subcommand, t_token *token)
{
	int		fd;
	char	*path;

	while (token)
	{
		path = ft_substr(token->value, 0, token->length);
		if (path[0] == '.' && path[1] == '/')
				subcommand->in_fd = open(path, O_RDONLY);
		free(path);
		if (token->type == TOKEN_LT)
		{
			if (!token->next || ft_strlen(token->next->value) == 0)
				return (ft_print_error(ESYN), false);
			if (token->next->type != TOKEN_SYMBOL && token->next->type != TOKEN_SQ
				&& token->next->type != TOKEN_DQ)
				return (ft_print_error(ESYN), false);
			path = ft_substr(token->next->value, 0, token->next->length);
			ft_close_in_files(subcommand);
			fd = open(path, O_RDONLY);
			if (fd == -1)
			{
				g_signal = 1;
				return (ft_print_error(ENOENT), free(path), false);
				subcommand->is_executable = false;
			}
			free(path);
			subcommand->in_fd = fd;
		}
		token = token->next;
	}
	return (true);
}
