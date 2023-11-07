/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/04 14:21:02 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "str.h"
#include "env.h"
#include "lexer_utils.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_expand_dollar(t_subcommand *subcommand, char *str)
{
	char	*expanded;
	char	*key;
	int		length;

	length = 0;
	while (str && str[length] != '$')
		length++;
	while (ft_is_valid_symbol(str[length]))
		length++;
	key = ft_substr(str, 1, length - 1);
	expanded = ft_get_cpy_env(subcommand, key);
	free(key);
	if (expanded)
		return (expanded);
	return ("");
}

int	ft_expand_token(t_subcommand *subcommand, t_token *tokens)
{
	char	*str;
	bool	is_sq;

	is_sq = false;
	while (tokens)
	{
		if (tokens->type == TOKEN_SQ)
			is_sq = !is_sq; 
		str = ft_substr(tokens->value, 0, tokens->length);
		if (ft_strchr(str, '$') && !is_sq)
		{
			tokens->value = ft_expand_dollar(subcommand, str);
			tokens->length = ft_strlen(ft_expand_dollar(subcommand, str));
		}
		tokens = tokens->next;
		free(str);
	}
	return (true);
}
