/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:14:02 by herbie            #+#    #+#             */
/*   Updated: 2023/07/10 11:51:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

t_command	ft_command_new(const char *raw)
{
	t_command	command;

	command.raw = raw;
	command.tokens = NULL;
	command.token_length = 0;
	return (command);
}

bool	ft_append_token(t_command *command, t_token token)
{
	t_token	*head;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	ft_memcpy(new_token, &token, sizeof(t_token));
	if (!command->tokens)
		command->tokens = new_token;
	else
	{
		head = command->tokens;
		while (command->tokens->next)
			command->tokens = command->tokens->next;
		command->tokens->next = new_token;
		command->tokens = head;
	}
	command->token_length++;
	return (true);
}

//! DEBUG ONLY
void	ft_debug_print_command(t_command command)
{
	int		i;
	t_token	*token;

	i = -1;
	printf("--------------\n");
	printf("Raw: %s\n", command.raw);
	printf("Token length: %d\n", command.token_length);
	token = command.tokens;
	printf("--------------\n");
	while (token && ++i < command.token_length)
	{
		printf("Token (%d): %.*s\n", token->length, token->length, token->value);
		token = token->next;
	}
	printf("--------------\n");
}
