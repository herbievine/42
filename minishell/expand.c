/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/16 17:45:52 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "str.h"
#include "env.h"
#include "char.h"
#include "lexer_utils.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_expand_dollar(t_subcommand *subcommand, char *str)
{
	char	*expanded;
	char	*key;
	int		length;
	int		i;

	length = 1;
	i = 0;
	while (str && str[i] != '$')
		i++;
	while (str[i + length] && ft_is_valid_symbol(str[i + length])
		&& str[i + length] != '\'' && str[i + length] != '"')
		length++;
	if (length == 1)
		return (ft_strdup("$"));
	if (str[i + 1] == '?')
		length = 2;
	key = ft_substr(str, i + 1, length - 1);
	expanded = ft_env_get(subcommand->envp, key);
	free(key);
	if (expanded)
		return (expanded);
	return (ft_strdup(""));
}

char	ft_type_token(char c, char type)
{
	if (c == '\'' && type != '\'' && type != '"')
		return (type = '\'');
	else if (c == '"' && type != '"' && type != '\'')
		return (type = '"');
	else if (c == '\'' && type == '\'')
		return (type = 2);
	else if (c == '"' && type == '"')
		return (type = 2);
	return (type);
}

void	ft_expand_token(t_subcommand *subcommand, t_token *tokens)
{
	char	limiter;
	char	*expanded;
	char	*str;
	int		i;

	while (tokens)
	{
		i = 0;
		limiter = 0;
		str = ft_substr(tokens->value, 0, tokens->length);
		while (str[i])
		{
			limiter = ft_type_token(str[i], limiter);
			if (str[i] == '$' && limiter != '\'')
			{
				expanded = ft_strjoin(ft_substr(str, 0, i),
						ft_expand_dollar(subcommand, str));
				while (str[i] && str[i] != '?' && ft_is_valid_symbol(str[i])
					&& str[i + 1] != '\'' && str[i + 1] != '"' && !ft_isspace(str[i+1]))
					++i;
				free(str);
				str = ft_strjoin(expanded, ft_substr(tokens->value, i + 1,
							ft_strlen(tokens->value) - i - 1));
				tokens->length = ft_strlen(str);
				tokens->value = ft_strdup(str);
			}
			i++;
		}
		tokens = tokens->next;
		free(str);
	}
}