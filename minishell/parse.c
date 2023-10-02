/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:04 by herbie            #+#    #+#             */
/*   Updated: 2023/09/20 16:20:30 by juliencros       ###   ########.fr       */
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

char	**ft_fill_args(t_token **token, t_subcommand *subcommand);
int		ft_args_count(t_token *token, char *path);
bool	ft_valid_token(t_token *token);

bool	ft_parse(t_token *tokens, t_subcommand *subcommand,
	t_subcommand *prev_subcommand)
{
	int		i;
	char	*path;

	i = -1;
	if (!tokens || !subcommand)
		return (false);
	if (prev_subcommand != NULL && subcommand)
	{
		if (subcommand->in_fd == 0)
			subcommand->in_fd = prev_subcommand->out_fd;
	}
	path = ft_substr(tokens->value, 0, tokens->length);
	if (ft_if_builtin(path))
	{
		subcommand->builtin = 1;
		subcommand->path = ft_strdup(path);
		free(path);
		t_token *tmp = tokens->next;
		subcommand->args = ft_fill_args(&tokens, subcommand);
		return (ft_builtin(subcommand, tokens), true);
	}
	free(path);
	if (!ft_set_cmd(tokens, subcommand)
		|| !ft_set_out_file(tokens, subcommand))
		return (false);
	subcommand->args = ft_fill_args(&tokens, subcommand);
	while (tokens->next != NULL && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	if (tokens->next != NULL && tokens->type == TOKEN_PIPE)
		return (ft_parse(tokens->next, subcommand->next, subcommand));
	return (true);
}

char	**ft_fill_args(t_token **token, t_subcommand *subcommand)
{
	int		i;
	char	*path;
	char	**args;
	t_token	*head;

	i = 0;
	head = *token;
	if (ft_args_count(head, subcommand->path) < 1 || !head)
		return (NULL);
	args = (char **)ft_calloc(ft_args_count(head, subcommand->path), sizeof(char *));
	if (!args)
		return (NULL);
	while (head != NULL && head->type != TOKEN_PIPE)
	{
		path = ft_substr(head->value, 0, head->length);
		if (ft_valid_token(head))
			head = head->next->next;
		if (!head || head->type == TOKEN_PIPE)
			break ;
		if (subcommand->path != NULL && ft_strschr(path, subcommand->path) != -1)
			head = head->next;
		free(path);
		path = ft_substr(head->value, 0, head->length);		
		args[i] = ft_strdup(path);
		free(path);
		head = head->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	ft_args_count(t_token *token, char *path)
{
	int	i;

	i = 0;
	if (path != NULL)
		i -= 1;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (ft_valid_token(token))
			i -= 2;
		token = token->next;
		i++;
	}
	return (i);
}

bool	ft_valid_token(t_token *token)
{
	if (token->type == TOKEN_LT
		|| token->type == TOKEN_LT_LT
		|| token->type == TOKEN_GT
		|| token->type == TOKEN_GT_GT)
		return (true);
	else
		return (false);
}
