/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:14:02 by herbie            #+#    #+#             */
/*   Updated: 2023/07/13 17:44:34 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "mem.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_command	*ft_command_new(const char *raw)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		ft_error(EMALLOC);
	command->in_fd = 0;
	command->out_fd = 1;
	command->raw = raw;
	command->path = NULL;
	command->args = NULL;
	command->mode = MODE_WRITE;
	command->is_heredoc = false;
	command->next = NULL;
	return (command);
}

bool	ft_create_commands_from_pipes(t_token **token_list, int token_length)
{
	t_token		*token;
	t_command	*command_list;

	token = *token_list;
	ft_command_new(command_list);
	while (token && token_length > 0)
	{
		if (token->type == TOKEN_PIPE)
		{
			if (!ft_build_commands_from_tokens(token_list, token_length))
				return (false);
		}
		token = token->next;
		token_length--;
	}
}

bool	ft_build_commands_from_tokens(t_token *token_list, int token_length)
{
	t_token		*token;
	t_command	*command_list;

	token = token_list;
	ft_command_new(command_list);
	while (token && token_length > 0)
	{
		// if (token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
		// {
		// 	if (!ft_set_outfile_fd(&token_list, command))
		// 		return (false);
		// }
		if (token->type == TOKEN_LT)
		{
			if (!ft_set_infile_fd(&token_list, command))
				return (false);
		}
		token = token->next;
		token_length--;
	}
}

bool	ft_set_infile_fd(t_token **token_list, t_command *command)
{
	int		fd;
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (token->type == TOKEN_LT && token->next)
		{
			printf("Infile found: %s\n", token->next->value);
			fd = open(token->next->value, O_RDONLY);
			if (fd == -1)
			{
				printf("minishell: %s: "ENOENT, token->next->value);
				return (false);
			}
			command->in_fd = fd;
		}
	}
}

//! DEBUG ONLY
void	ft_debug_print_command(t_token *token_list, int token_length)
{
	int		i;
	t_token	*token;

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
