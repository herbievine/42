/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:16 by herbie            #+#    #+#             */
/*   Updated: 2023/10/28 13:15:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "subcommand.h"
#include "structs.h"
#include "mem.h"
#include "error.h"
#include "token.h"
#include "here_doc.h"
#include "find_out_file.h"
#include "find_in_file.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>

t_subcommand	*ft_subcommand_new(char **envp, char **cpy_envp)
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
	subcommand->out_file_name = NULL;
	subcommand->envp = envp;
	subcommand->cpy_envp = cpy_envp;
	subcommand->mode = MODE_WRITE;
	subcommand->is_heredoc = false;
	subcommand->next = NULL;
	return (subcommand);
}

t_subcommand	*ft_build_subcommand(t_token *token_start, int token_length , char **envp, char **cpy_envp)
{
	t_subcommand	*subcommand;

	subcommand = ft_subcommand_new(envp, cpy_envp);
	if (!subcommand)
		return (NULL);
	if (!ft_set_here_doc(subcommand, token_start, token_length))
		return (free(subcommand), NULL);
	if (!ft_set_in_fd(subcommand, token_start, token_length))
		return (free(subcommand), NULL);
	if (!ft_set_out_fd(subcommand, token_start, token_length))
		return (free(subcommand), NULL);
	return (subcommand);
}

t_subcommand	*ft_find_next_subcommand(t_command *command, int *token_index, char **envp, char **cpy_envp)
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
		return (ft_build_subcommand(token, command->token_length, envp, cpy_envp));
	}
	else if (*token_index == 0 || pipe_offset > 0)
	{
		*token_index += pipe_offset + 1;
		return (ft_build_subcommand(token, pipe_offset, envp, cpy_envp));
	}
	return (NULL);
}

bool	ft_create_subcommands(t_command *command , char **envp, char **cpy_envp)
{
	int				token_index;
	t_subcommand	*subcommand;
	t_subcommand	*head;

	token_index = 0;
	subcommand = ft_find_next_subcommand(command, &token_index , envp, cpy_envp);
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
		subcommand = ft_find_next_subcommand(command, &token_index , envp, cpy_envp);
	}
	return (true);
}
