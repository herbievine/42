/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/10 17:23:41 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_in_file.h"
#include <stdio.h>
#include "error.h"
#include "str.h"
#include <unistd.h>
#include <fcntl.h>

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
		if (token->type == TOKEN_LT)
		{
			if (!token->next)
				return (printf(M""ESYN" `newline'\n"), false);
			if (token->next->type != TOKEN_SYMBOL)
				return (printf(M""ESYN" `%s'\n", token->next->value), false);
			path = ft_substr(token->next->value, 0, token->next->length);
			ft_close_in_files(subcommand);
			fd = open(path, O_RDONLY);
			if (fd == -1)
			{
				g_signal = 1;
				return (printf(M"%s: "ENOENT"\n", path), free(path), false);
			}
			free(path);
			subcommand->in_fd = fd;
		}
		token = token->next;
	}
	return (true);
}
