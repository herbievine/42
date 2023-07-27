/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:16 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 16:02:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subcommand.h"
#include "structs.h"
#include "mem.h"
#include "error.h"
#include "token.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>

t_subcommand	*ft_subcommand_new(void)
{
	t_subcommand	*subcommand;

	subcommand = ft_calloc(sizeof(t_subcommand), 1);
	if (!subcommand)
		return (NULL);
	subcommand->in_fd = 0;
	subcommand->out_fd = 1;
	subcommand->path = NULL;
	subcommand->args = NULL;
	subcommand->mode = MODE_WRITE;
	subcommand->is_heredoc = false;
	subcommand->next = NULL;
	return (subcommand);
}

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

bool	ft_set_out_fd(t_subcommand *subcommand, t_token *token, int token_length)
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

t_subcommand	*ft_build_subcommand(t_token *token_start, int token_length)
{
	t_subcommand	*subcommand;

	subcommand = ft_subcommand_new();
	if (!subcommand)
		return (NULL);
	if (!ft_set_in_fd(subcommand, token_start, token_length))
		return (free(subcommand), NULL);
	if (!ft_set_out_fd(subcommand, token_start, token_length))
		return (free(subcommand), NULL);
	return (subcommand);
}

t_subcommand	*ft_find_next_subcommand(t_command *command, int *token_index)
{
	int				i;
	t_token			*token;
	int				pipe_offset;

	token = command->tokens;
	if (!token || *token_index >= command->token_length)
		return (NULL);
	i = -1;
	while (++i < *token_index)
		token = token->next;
	pipe_offset = ft_find_next_pipe(token);
	if (pipe_offset == PIPE_NOT_FOUND)
	{
		*token_index = command->token_length;
		return (ft_build_subcommand(token, command->token_length));
	}
	else if (*token_index == 0 || pipe_offset > 0)
	{
		*token_index += pipe_offset + 1;
		return (ft_build_subcommand(token, pipe_offset));
	}
	return (NULL);
}

bool	ft_create_subcommands(t_command *command)
{
	int				token_index;
	t_subcommand	*subcommand;
	t_subcommand	*head;

	token_index = 0;
	subcommand = ft_find_next_subcommand(command, &token_index);
	while (subcommand)
	{
		if (!command->subcommands)
			command->subcommands = subcommand;
		else
		{
			head = command->subcommands;
			while (command->subcommands->next)
				command->subcommands = command->subcommands->next;
			command->subcommands->next = subcommand;
			command->subcommands = head;
		}
		subcommand = ft_find_next_subcommand(command, &token_index);
	}
	return (true);
}
