/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_out_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:18:30 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/18 14:15:48 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_out_file.h"
#include "error.h"
#include "str.h"
#include "display.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

bool	ft_check_if_others_pipe(t_token *token);

bool	ft_set_out_file(t_token *token, t_subcommand *subcommand)
{
	t_token	*first_token;

	if (!token || token->type == TOKEN_PIPE
		|| ft_check_if_others_pipe(token))
		return (true);
	first_token = token;
	while (first_token->next != NULL && first_token->type != TOKEN_PIPE)
	{
		if (first_token->type == TOKEN_GT || first_token->type == TOKEN_GT_GT)
			return (ft_set_out_fd(subcommand,
					first_token, first_token->length), true);
		first_token = first_token->next;
	}
	return (true);
}

bool	ft_check_if_others_pipe(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->type == TOKEN_PIPE
			|| token->type == TOKEN_GT
			|| token->type == TOKEN_GT_GT)
			return (false);
		token = token->next;
	}
	return (true);
}

static void	ft_error_out_file(t_subcommand *subcommand,
	t_token *token, char *error)
{
	ft_putstr_fd(M, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	subcommand->is_executable = false;
	g_signal = 1;
}

bool	ft_set_out_fd(t_subcommand *subcommand,
	t_token *token, int token_length)
{
	char	*path;
	int		fd;

	while (token && token_length > 0)
	{
		if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
		{
			if (!token->next || token->next->type != TOKEN_SYMBOL)
				return (ft_error_out_file(subcommand, token, ESYN), false);
			path = ft_substr(token->next->value, 0, token->next->length);
			if (token->type == TOKEN_GT)
				fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				ft_error_out_file(subcommand, token, ENOENT);
			else
				subcommand->out_file_name = ft_strdup(path);
			free(path);
			return (subcommand->out_fd = fd, true);
		}
		token = token->next;
		token_length--;
	}
	return (true);
}
