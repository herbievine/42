/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_out_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:18:30 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/22 18:05:18 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_out_file.h"
#include "error.h"
#include "str.h"
#include "display.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * @brief The ft_handle_open function takes in a pointer to a subcommand and a
 * pointer to a token. It opens the file specified by the token and throws the
 * appropriate error message if the file is invalid. It returns the file
 * descriptor of the file.
 * 
 * @param subcommand 
 * @param token 
 * @return int 
 */
static int	ft_handle_open(t_subcommand **subcommand, t_token *token)
{
	char	*path;
	int		fd;

	path = ft_substr(token->next->value, 0, token->next->length);
	if (!path)
		return (g_signal = 1, -1);
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

/**
 * @brief The ft_find_outfile function takes in a pointer to a subcommand and a
 * pointer to a token. It iterates through the tokens until it reaches a pipe
 * token. If it finds a redirection token, it calls the ft_handle_open
 * function. If the file is invalid, it returns false. Otherwise, it sets the
 * out_fd of the subcommand to the file descriptor of the file.
 * 
 * @param subcommand 
 * @param token 
 * @return true 
 * @return false 
 */
bool	ft_find_outfile(t_subcommand *subcommand, t_token *token)
{
	int	fd;

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
