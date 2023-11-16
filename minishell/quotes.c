/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:33 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/16 16:49:16 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include "find_cmds.h"
#include "expand.h"
#include <stdio.h>

void ft_change_token_type(t_token *token, char limitter)
{
	if (limitter == '"')
		token->type = TOKEN_DQ;
	else if (limitter == '\'')
		token->type = TOKEN_SQ;
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
		i = -1;
		while (str[++i])
		{
			limitter = ft_type_token(str[i], limitter && limitter != 2);
			if (str[i] == '"' || str[i] == '\'')
			{
				splited_str = ft_split(str, limitter);
				if (splited_str[1] && splited_str[2])
					tokens->value = ft_fmt_path(splited_str[0],
										splited_str[1], splited_str[2]);
				else if (splited_str[1])
					tokens->value = ft_strjoin(splited_str[0], splited_str[1]);
				else if (splited_str[0])
					tokens->value = ft_strdup(splited_str[0]);
				else
					tokens->value = ft_strdup("");
				tokens->length = ft_strlen(tokens->value);
				ft_change_token_type(tokens, limitter);
				ft_free_array(splited_str, -1);
			}
		}
		tokens = tokens->next;
	}
}