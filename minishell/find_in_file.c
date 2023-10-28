/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/24 17:41:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_in_file.h"
#include <stdio.h>
#include "error.h"
#include <unistd.h>
#include <fcntl.h>

bool	ft_set_in_fd(t_subcommand *subcommand, t_token *token, int token_length)
{
	int		fd;
	char	*path;

	while (token && token_length > 0)
	{
		if (token->type == TOKEN_LT)
		{
			if (!token->next)
				return (printf(M""ESYN" `newline'\n"), false);
			if (token->next->type != TOKEN_SYMBOL)
				return (printf(M""ESYN" `%s'\n", token->next->value), false);
			path = (char *)token->next->value;
			path[token->next->length] = '\0';
			fd = open(path, O_RDONLY);
			if (fd == -1)
				printf(M"%s: "ENOENT"\n", token->next->value);
			return (subcommand->in_fd = fd, true);
		}
		token = token->next;
		token_length--;
	}
	return (true);
}
