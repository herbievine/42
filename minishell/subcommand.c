/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:16 by herbie            #+#    #+#             */
/*   Updated: 2023/11/26 08:42:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subcommand.h"
#include "structs.h"
#include "mem.h"
#include "error.h"
#include "free.h"
#include "token.h"
#include "here_doc.h"
#include "find_out_file.h"
#include "find_in_file.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>

t_subcommand	*ft_subcommand_new(char **env)
{
	t_subcommand	*subcommand;

	subcommand = ft_calloc(sizeof(t_subcommand), 1);
	if (!subcommand)
		return (NULL);
	subcommand->in_fd = -1;
	subcommand->out_fd = -1;
	subcommand->builtin = 0;
	subcommand->path = NULL;
	subcommand->args = NULL;
	subcommand->envp = env;
	subcommand->mode = MODE_WRITE;
	subcommand->is_executable = true;
	subcommand->is_heredoc = false;
	subcommand->next = NULL;
	return (subcommand);
}

t_subcommand	*ft_build_subcommand(char **env)
{
	t_subcommand	*subcommand;

	subcommand = ft_subcommand_new(env);
	if (!subcommand)
		return (NULL);
	return (subcommand);
}

t_subcommand	*ft_find_next_subcommand(t_command *command, int *token_index,
	char **env)
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
		return (ft_build_subcommand(env));
	}
	else if (*token_index == 0 || pipe_offset > 0)
	{
		*token_index += pipe_offset + 1;
		return (ft_build_subcommand(env));
	}
	return (NULL);
}

bool	ft_create_subcommands(t_command *command, char **env)
{
	int				token_index;
	t_subcommand	*subcommand;
	t_subcommand	*head;

	token_index = 0;
	subcommand = ft_find_next_subcommand(command, &token_index, env);
	while (subcommand)
	{
		if (!command->subcommands)
		{
			command->subcommands = subcommand;
			command->subcommand_length = 1;
		}
		else
		{
			head = command->subcommands;
			while (command->subcommands->next)
				command->subcommands = command->subcommands->next;
			command->subcommands->next = subcommand;
			command->subcommands = head;
			command->subcommand_length++;
		}
		subcommand = ft_find_next_subcommand(command, &token_index, env);
	}
	return (true);
}
