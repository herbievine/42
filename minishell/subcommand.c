/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:16 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 13:15:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subcommand.h"
#include "structs.h"
#include "mem.h"
#include "token.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

t_subcommand	*ft_build_subcommand(void)
{
	t_subcommand	*subcommand;

	subcommand = ft_subcommand_new();
	if (!subcommand)
		return (NULL);
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
// 	command->subcommand_count++;
// 	return (true);
// }

t_subcommand	*ft_find_next_subcommand(t_command *command)
{
	int				i;
	static int		token_index;
	t_token			*token;
	int				pipe_offset;

	token = command->tokens;
	if (!token || token_index >= command->token_count)
		return (NULL);
	i = -1;
	while (++i < token_index)
		token = token->next;
	pipe_offset = ft_find_next_pipe(token);
	if (token_index == 0)
		return (token_index = pipe_offset + 1, ft_build_subcommand());
	if (pipe_offset == PIPE_NOT_FOUND)
		return (token_index = command->token_count, ft_build_subcommand());
	if (pipe_offset > 0)
		return (token_index += pipe_offset + 1, ft_build_subcommand());
	return (NULL);
}

bool	ft_create_subcommands(t_command *command)
{
	t_subcommand	*subcommand;

	subcommand = ft_find_next_subcommand(command);
	while (subcommand)
		subcommand = ft_find_next_subcommand(command);
	return (true);
}
