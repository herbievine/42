/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:14:02 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 15:48:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "mem.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_command ft_command_new(void)
{
	t_command command;

	command.tokens = NULL;
	command.token_length = 0;
	command.subcommands = NULL;
	command.subcommand_length = 0;
	return (command);
}

// bool	ft_create_commands_from_pipes(t_token **token_list, int token_length)
// {
// 	t_token		*token;
// 	t_command	command;

// 	token = *token_list;
// 	while (token && token_length > 0)
// 	{
// 		if (token->type == TOKEN_PIPE)
// 		{
// 			if (!ft_build_commands_from_tokens(token_list, token_length))
// 				return (false);
// 		}
// 		token = token->next;
// 		token_length--;
// 	}
// }

// bool	ft_append_command(t_token **commands, t_token token)
// {
// 	t_token	*head;
// 	t_token	*new_token;

// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 		return (false);
// 	ft_memcpy(new_token, &token, sizeof(t_token));
// 	if (!*tokens)
// 		*tokens = new_token;
// 	else
// 	{
// 		head = *tokens;
// 		while ((*tokens)->next)
// 			*tokens = (*tokens)->next;
// 		(*tokens)->next = new_token;
// 		*tokens = head;
// 	}
// 	return (true);
// }

// bool	ft_clear_commands(t_token **tokens)
// {
// 	t_token	*next;

// 	while (*tokens)
// 	{
// 		next = (*tokens)->next;
// 		free(*tokens);
// 		*tokens = next;
// 	}
// 	*tokens = NULL;
// 	return (true);
// }

// bool	ft_build_commands_from_tokens(t_token *token_list, int token_length)
// {
// 	t_token		*token;
// 	t_command	*command_list;

// 	token = token_list;
// 	ft_command_new(command_list);
// 	while (token && token_length > 0)
// 	{
// 		// if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
// 		// {
// 		// 	if (!ft_set_outfile_fd(&token_list, command))
// 		// 		return (false);
// 		// }
// 		if (token->type == TOKEN_LT)
// 		{
// 			if (!ft_set_infile_fd(&token_list, command))
// 				return (false);
// 		}
// 		token = token->next;
// 		token_length--;
// 	}
// }

// bool	ft_set_infile_fd(t_token **token_list, t_command *command)
// {
// 	int		fd;
// 	t_token	*token;

// 	token = *token_list;
// 	while (token)
// 	{
// 		if (token->type == TOKEN_LT && token->next)
// 		{
// 			printf("Infile found: %s\n", token->next->value);
// 			fd = open(token->next->value, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				printf("minishell: %s: "ENOENT, token->next->value);
// 				return (false);
// 			}
// 			command->in_fd = fd;
// 		}
// 	}
// }

//! DEBUG ONLY
void ft_debug_print_command(t_token *token_list, int token_length)
{
	int i;
	t_token *token;

	i = -1;
	printf("--------------\n");
	printf("Token length: %d\n", token_length);
	token = token_list;
	printf("--------------\n");
	while (token && ++i < token_length)
	{
		printf("Token (%d): %.*s\n", token->length, token->length, token->value);
		token = token->next;
	}
	printf("--------------\n");
}
