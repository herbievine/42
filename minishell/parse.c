/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:04 by herbie            #+#    #+#             */
/*   Updated: 2023/10/03 13:19:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "structs.h"
#include "mem.h"
#include "error.h"
#include "find_in_file.h"
#include "find_cmds.h"
#include "find_out_file.h"
#include "builtin.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "str2.h"

static char	**ft_fill_args(t_token **token, t_subcommand *subcommand);
static int	ft_arg_count(t_token *token, char *path);

bool	ft_parse(t_token *tokens, t_subcommand *subcommand,
	t_subcommand *prev_subcommand)
{
	char	*path;

	if (prev_subcommand != NULL && subcommand->in_fd == 0)
		subcommand->in_fd = prev_subcommand->out_fd;
	// path = ft_substr(tokens->value, 0, tokens->length);
	// if (ft_if_builtin(path))
	// {
	// 	subcommand->builtin = 1;
	// 	subcommand->path = ft_strdup(path);
	// 	free(path);
	// 	t_token *tmp = tokens->next;
	// 	subcommand->args = ft_fill_args(&tokens, subcommand);
	// 	return (ft_builtin(subcommand, tokens), true);
	// }
	// free(path);
	if (!ft_set_path(subcommand, tokens) || !ft_set_out_file(tokens, subcommand))
		return (false);
	subcommand->args = ft_fill_args(&tokens, subcommand);
	while (tokens->next != NULL && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	if (tokens->next && tokens->type == TOKEN_PIPE && subcommand->next)
		return (ft_parse(tokens->next, subcommand->next, subcommand));
	return (true);
}

bool	ft_is_io_symbol(t_token *token)
{
	if (token->type == TOKEN_LT || token->type == TOKEN_LT_LT
		|| token->type == TOKEN_GT || token->type == TOKEN_GT_GT)
		return (true);
	else
		return (false);
}

static char	**ft_fill_args(t_token **token, t_subcommand *subcommand)
{
	int		i;
	char	*path;
	char	**args;
	t_token	*head;

	head = *token;
	if (ft_arg_count(head, subcommand->path) < 1 || !head)
		return (NULL);
	args = ft_calloc(ft_arg_count(head, subcommand->path), sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (head != NULL && head->type != TOKEN_PIPE)
	{
		if (ft_is_io_symbol(head))
			head = head->next->next;
		if (!head || head->type == TOKEN_PIPE)
			break ;
		args[i] = ft_substr(head->value, 0, head->length);
		head = head->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static int	ft_arg_count(t_token *token, char *path)
{
	int	i;

	i = 0;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (ft_is_io_symbol(token))
			i -= 2;
		token = token->next;
		i++;
	}
	return (i);
}
