/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:04 by herbie            #+#    #+#             */
/*   Updated: 2023/08/23 10:43:49 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "structs.h"
#include "error.h"
#include "find_in_file.h"
#include "find_cmds.h"
#include "find_out_file.h"
#include "builtin.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "str2.h"

char	**ft_fill_args(t_token *token, t_subcommand *subcommand);
int		ft_args_count(t_token *token);
bool	ft_valid_token(t_token *token);

bool	ft_parse(t_token *tokens, t_subcommand *subcommand,
	t_subcommand *prev_subcommand)
{
	int		i;
	char	*path;

	i = 0;
	// if (prev_subcommand != NULL)
	// {
	// 	subcommand->in_fd = prev_subcommand->out_fd;
	// 	ft_set_in_fd(subcommand, tokens, tokens->length);
	// }
	path = (char *)tokens->value;
	path[tokens->length] = '\0';
	if (ft_if_builtin(path))
	{
		subcommand->builtin = 1;
		subcommand->path = ft_strdup(path);
		// subcommand->args = ft_fill_args(tokens->next, subcommand);
		return (ft_builtin(subcommand, tokens), true);
	}
	if (!ft_set_cmd(tokens, subcommand)
		|| !ft_set_out_file(tokens, subcommand))
		return (true);
	subcommand->args = ft_fill_args(tokens, subcommand);
	while (tokens->next != NULL && tokens->type != TOKEN_PIPE)
		tokens = tokens->next;
	if (tokens->next != NULL && tokens->type == TOKEN_PIPE)
		return (ft_parse(tokens->next, subcommand->next, subcommand));
	return (true);
}

// char	**ft_fill_args(t_token *token, t_subcommand *subcommand)
// {
// 	int		i;
// 	char	*path;
// 	char	**args;

// 	i = 0;
// 	if (ft_args_count(token) <= 1 && subcommand->path != NULL)
// 		return (NULL);
// 	args = malloc(sizeof(char *) * (ft_args_count(token)));
// 	if (!args)
// 		return (NULL);
// 	while (token != NULL && token->type != TOKEN_PIPE)
// 	{
// 		if (ft_valid_token(token))
// 			token = token->next->next;
// 		if (!token || token->type == TOKEN_PIPE)
// 			return (args);
// 		path = (char *)token->value;
// 		path[token->length] = '\0';
// 		if (subcommand->path != NULL && ft_strschr(path, subcommand->path) != -1)
// 		{
// 			token = token->next;
// 			printf ("path = %s\n", path);
// 		}
// 		if (!token || token->type == TOKEN_PIPE)
// 			return (args);
// 		path = (char *)token->value;
// 		path[token->length] = '\0';
// 		args[i] = ft_strdup(path);
// 		token = token->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

/**
 * @brief 
 * 
 * @param token 
 * @param subcommand 
 * @return char** 
 */
char **ft_fill_args(t_token *token, t_subcommand *subcommand)
{
	int		i;
	char	*path;
	char	**args;
	t_token *tmp;

	i = 0;
	tmp = token;
	if (ft_args_count(token) < 1 && subcommand->path != NULL)
		return (NULL);
	args = malloc(sizeof(char *) * (ft_args_count(token) + 1));
	if (!args)
		return (NULL);
	if(ft_valid_token(token))
		token = token->next->next;
	while (tmp != NULL && tmp->type != TOKEN_PIPE && !ft_valid_token(tmp))
	{
		// if (token->type == TOKEN_DQ || token->type == TOKEN_SQ)
		// {
		// 	args[i] = ft_substr(token->value, 0, token->length - 2);
		// 	i++;
		// 	if (!token->next || token->next->type == TOKEN_PIPE || !args[i])
		// 		return (args);
		// }printf("token->type = %d\n", token->type);
		path = (char *)tmp->value;
		path[tmp->length] = '\0';
		if (subcommand->path != NULL && ft_strschr(subcommand->path, path) != -1)
			tmp = tmp->next;
		if (!tmp || tmp->type == TOKEN_PIPE)
			return (args);
		path = (char *)tmp->value;
		path[tmp->length] = '\0';
		args[i] = ft_strdup(path);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 * @brief 
 * 
 * @param token 
 * @return int 
 */
int	ft_args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (ft_valid_token(token))
			i = i - 2;
		// if (token->type == TOKEN_DQ || token->type == TOKEN_SQ)
		// 	i = i - 1;
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
