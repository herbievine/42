/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_out_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:18:30 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/20 14:19:21 by herbie           ###   ########.fr       */
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
	if (!token || token->type == TOKEN_PIPE
		|| ft_check_if_others_pipe(token))
		return (true);
	return (ft_set_out_fd(subcommand, token));
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

int	ft_handle_open(t_subcommand **subcommand, t_token *token)
{
	char	*path;
	int		fd;

	path = ft_substr(token->next->value, 0, token->next->length);
	if ((*subcommand)->out_fd > 0)
		close((*subcommand)->out_fd);
	if (token->type == TOKEN_GT)
		fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_perror("minishell: ");
		(*subcommand)->is_executable = false;
		g_signal = 1;
	}
	else
		(*subcommand)->out_file_name = ft_strdup(path);
	free(path);
	return (fd);
}

bool	ft_set_out_fd(t_subcommand *subcommand, t_token *token)
{
	char	*path;
	int		fd;

	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
		{
			if (!token->next || (token->next->type != TOKEN_SYMBOL
					&& token->next->type != TOKEN_DQ
					&& token->next->type != TOKEN_SQ))
			{
				ft_error(ESYN);
				subcommand->is_executable = false;
				return (g_signal = 1, false);
			}
			fd = ft_handle_open(&subcommand, token);
			if (fd == -1)
				return (false);
			subcommand->out_fd = fd;
		}
		token = token->next;
	}
	return (true);
}
