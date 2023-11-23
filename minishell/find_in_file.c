/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/23 11:02:12 by juliencros       ###   ########.fr       */
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
	if ((*subcommand)->is_heredoc)
		unlink(".here_doc_fd");
	fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_perror("minishell: ");
		(*subcommand)->is_executable = false;
		g_signal = 1;
	}
	free(path);
	return (fd);
}

/**
 * @brief The ft_find_infile function takes in a pointer to a subcommand and a
 * pointer to a token. It iterates through the tokens until it reaches a pipe
 * token. If it finds a redirection token, it calls the ft_handle_open
 * function. If the file is invalid, it returns false. Otherwise, it sets the
 * in_fd of the subcommand to the file descriptor of the file.
 * 
 * @param subcommand 
 * @param token 
 * @return true 
 * @return false 
 */
bool	ft_set_infile(t_subcommand *subcommand, t_token *token)
{
	int	fd;

	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_LT)
		{
			if (!token->next || ft_strlen(token->next->value) == 0
				&& token->next->type != TOKEN_SYMBOL
				&& token->next->type != TOKEN_SQ
				&& token->next->type != TOKEN_DQ)
			{
				ft_error(ESYN, NULL);
				subcommand->is_executable = false;
				return (g_signal = 1, false);
			}
			fd = ft_handle_open(&subcommand, token);
			if (fd == -1)
				return (false);
			subcommand->in_fd = fd;
		}
		token = token->next;
	}
	return (true);
}
