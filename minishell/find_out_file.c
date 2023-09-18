/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_out_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:18:30 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/21 17:21:24 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_out_file.h"
#include "error.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

bool	ft_check_if_others_pipe(t_token *token);

bool	ft_set_out_file(t_token *token, t_subcommand *subcommand)
{
	char	*path;
	int		fd;
	t_token	*first_token;

	if (!token || token->type == TOKEN_PIPE 
		|| subcommand->in_fd == -1 || ft_check_if_others_pipe(token))
		return (true);
	first_token = token;
	while (token->next != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
			return (ft_set_out_fd(subcommand, first_token, token->length), true);
		token = token->next;
	}
	return (true);
}

bool	create_out_fd_without_gt(t_subcommand *subcommand)
{
	subcommand->out_fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (!subcommand->out_fd)
		return (false);
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

bool	ft_set_out_fd(t_subcommand *subcommand,
	t_token *token, int token_length)
{
	int		fd;
	char	*path;

	while (token && token_length > 0)
	{
		if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
		{
			if (!token->next)
				return (printf(M""ESYN" `newline'\n"), false);
			if (token->next->type != TOKEN_SYMBOL)
				return (printf(M""ESYN" `%s'\n", token->next->value), false);
			path = (char *)token->next->value;
			path[token->next->length] = '\0';
			if (token->type == TOKEN_GT)
				fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				printf(M"%s: "ENOENT"\n", token->next->value);
			return (subcommand->out_fd = fd, true);
		}
		token = token->next;
		token_length--;
	}
	return (true);
}
