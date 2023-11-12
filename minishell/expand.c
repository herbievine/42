/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/11 14:17:12 by juliencros       ###   ########.fr       */
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
	int 	i;

	length = 0;
	i = 0;
	while (str && str[i] != '$')
		i++;
	while (str[i + length] && ft_is_valid_symbol(str[length]))
		length++;
	if (length == 1)
		return (ft_strdup("$"));
	if (str[i + 1] == '?')
		length = 1;
	key = ft_substr(str, i+1, length);
	expanded = ft_get_cpy_env(subcommand, key);
	free(key);
	if (expanded)
		return (expanded);
	return (ft_strdup("")); // TODO: check if this is the right thing to do
}

int	ft_expand_token(t_subcommand *subcommand, t_token *tokens)
{
	char	*str;
	int		i;
	int 	j;
	char	*expanded;

	i = 0;
	j = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_SQ)
			return (true);
		str = ft_substr(tokens->value, 0, tokens->length);
		while (str[i] && str[i] != '$')
			i++;
		while (str[i + j] && str[i + j] != ' ')
			j++;
		free(str);
		str = ft_substr(tokens->value, i, j);
		if (str && ft_strchr(str, '$') && ft_strlen(str) > 1)
		{
			expanded = ft_strjoin(ft_substr(tokens->value, 0, i), ft_expand_dollar(subcommand, str));
			free(str);
			str = ft_strjoin(expanded, ft_substr(tokens->value, i + j, ft_strlen(tokens->value) - i - j));
			tokens->length = ft_strlen(str);
			// free(tokens->value);
			tokens->value = ft_strdup(str);
		}
		tokens = tokens->next;
		free(str);
	}
	return (true);
}
