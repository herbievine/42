/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:33 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/26 12:22:22 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include "find_cmds.h"
#include "expand.h"
#include <stdio.h>

void	ft_change_token_type(t_token *token, char limitter)
{
	if (limitter == '"')
		token->type = TOKEN_DQ;
	else if (limitter == '\'')
		token->type = TOKEN_SQ;
}

bool	ft_clean_string(char *str, char limitter,
	t_subcommand *subcommand, t_token *tokens)
{
	char	**splited_str;
	char	*new_str;

	free((char *)tokens->value);
	splited_str = ft_split(str, limitter);
	if (!splited_str)
		return (tokens->value = ft_strdup(""),
			subcommand->is_executable = false, false);
	new_str = str_c(splited_str, "");
	ft_free_array(splited_str, -1);
	if (!new_str)
		return (tokens->value = ft_strdup(""),
			subcommand->is_executable = false, false);
	tokens->value = new_str;
	tokens->length = ft_strlen(tokens->value);
	ft_change_token_type(tokens, limitter);
	return (true);
}

void	ft_suppress_quotes(t_subcommand *subcommands, t_token *tokens)
{
	char	*str;
	char	**splited_str;
	char	limitter;
	int		i;

	limitter = 0;
	while (tokens)
	{
		str = ft_substr(tokens->value, 0, tokens->length);
		if (!str)
			return (subcommands->is_executable = false, g_signal = 1, (void)0);
		i = -1;
		while (str && str[++i])
		{
			limitter = ft_type_token(str[i], limitter && limitter != 2);
			if (str[i] == '"' || str[i] == '\'')
			{
				if (!ft_clean_string(str, str[i], subcommands, tokens))
					return (free(str), g_signal = 1, (void)0);
				break ;
			}
		}
		free(str);
		tokens = tokens->next;
	}
}
