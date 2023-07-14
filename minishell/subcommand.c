/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:16 by herbie            #+#    #+#             */
/*   Updated: 2023/07/14 18:39:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subcommand.h"
#include "structs.h"
#include "mem.h"
#include "token.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

// bool	ft_build_subcommand_from_tokens(t_token **tokens, int token_length)
// {
// 	t_token			*token;
// 	t_token			*head;
// 	t_subcommand	*subcommand;
// 	int				i;

// 	i = 0;
// 	token = *tokens;
// 	while (token && i < token_length)
// 	{
// 		if (token->type == TOKEN_PIPE)
// 		{
// 			subcommand = ft_subcommand_new();
// 			if (!ft_build_subcommand(tokens, token_length))
// 				return (false);
// 		}
// 		token = token->next;
// 		i++;
// 	}
// 	return (true);
// }

bool	ft_append_subcommand(t_command *command, t_token *tokens, int size)
{
	t_subcommand	*subcommand;
	t_subcommand	*head;

	subcommand = ft_subcommand_new();
	if (!subcommand)
		return (false);
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
	command->subcommand_count++;
	return (true);
}

bool	ft_create_subcommands(t_command *command, t_token **tokens, int token_length)
{
	t_token			*token;
	int				i;
	int				cmd_index;
	int				pipe_offset;

	i = 0;
	cmd_index = 0;
	token = *tokens;
	while (token && i < token_length)
	{
		pipe_offset = ft_next_pipe(token);
		if (pipe_offset == PIPE_NOT_FOUND)
		{
			while (token && i < token_length)
			{
				printf("token to pipe: (%d): %.*s\n", cmd_index, token->length, token->value);
				i++;
				token = token->next;
			}
			continue ;
		}
		if (pipe_offset > 0)
		{
			while (pipe_offset > 0)
			{
				printf("token to pipe (%d): %.*s\n", cmd_index, token->length, token->value);
				i++;
				token = token->next;
				pipe_offset--;
			}
		// 	// subcommand = ft_subcommand_new();
		// 	// if (!ft_build_subcommand(tokens, pipe_offset))
		// 	// 	return (false);
		}
		i++;
		token = token->next;
		cmd_index++;
		// else 
	}
	return (true);
}
