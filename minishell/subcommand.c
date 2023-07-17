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

// 1. function to build new subcommand (malloc, set default values)
// 2. function to append subcommand to command (linked lists)
// 3. function to build subcommand from tokens (appropriate fd,
// path, args, mode, etc...)
// 4. function to create subcommands from tokens (split by pipes)

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
	int	fd;

	printf("token_length: %d\n", token_length);

	while (token && token_length > 0)
	{
		if (token->type == TOKEN_LT)
		{
			if (!token->next)
			{
				printf(M""ESYN" `newline'\n");
				return (false);
			}
			if (token->next->type != TOKEN_SYMBOL)
			{
				printf(M""ESYN" `%s'\n", token->next->value);
				return (false);
			}
			fd = open(token->next->value, O_RDONLY);
			if (fd == -1)
				printf(M"%s: "ENOENT"\n", token->next->value);
			return (subcommand->in_fd = fd, true);
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
	// printf("in_fd: %d\n", subcommand->in_fd);
	return (subcommand);
}

// bool	ft_append_subcommand(t_command *command)
// {
// 	t_subcommand	*subcommand;
// 	t_subcommand	*head;

// 	subcommand = ft_subcommand_new();
// 	if (!subcommand)
// 		return (false);
// 	if (!command->subcommands)
// 		command->subcommands = subcommand;
// 	else
// 	{
// 		head = command->subcommands;
// 		while (command->subcommands->next)
// 			command->subcommands = command->subcommands->next;
// 		command->subcommands->next = subcommand;
// 		command->subcommands = head;
// 	}
// 	command->subcommand_length++;
// 	return (true);
// }

t_subcommand	*ft_find_next_subcommand(t_command *command)
{
	int				i;
	static int		token_index;
	t_token			*token;
	int				pipe_offset;

	token = command->tokens;
	if (!token || token_index >= command->token_length)
		return (NULL);
	i = -1;
	while (++i < token_index)
		token = token->next;
	pipe_offset = ft_find_next_pipe(token);
	if (pipe_offset == PIPE_NOT_FOUND)
	{
		token_index = command->token_length;
		return (ft_build_subcommand(token, command->token_length));
	}
	if (token_index == 0)
	{
		token_index = pipe_offset + 1;
		return (ft_build_subcommand(token, pipe_offset));
	}
	if (pipe_offset > 0)
	{
		token_index += pipe_offset + 1;
		return (ft_build_subcommand(token, pipe_offset));
	}
	return (NULL);
}

bool	ft_create_subcommands(t_command *command)
{
	t_subcommand	*subcommand;

	subcommand = ft_find_next_subcommand(command);
	while (subcommand)
	{
		t_subcommand	tmp;
		ft_memcpy(&tmp, subcommand, sizeof(t_subcommand));
		printf(SUBCOMMAND_FMT, SUBCOMMAND_ARG(tmp));
		subcommand = ft_find_next_subcommand(command);
	}
	return (true);
}
