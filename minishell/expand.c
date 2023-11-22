/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/22 09:23:23 by juliencros       ###   ########.fr       */
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
		return ('\'');
	else if (c == '"' && type != '"' && type != '\'')
		return ('"');
	else if (c == '\'' && type == '\'')
		return (2);
	else if (c == '"' && type == '"')
		return (2);
	return (type);
}

void	ft_is_exit_status(t_subcommand *subcommand, t_token *token,  char *str, int i)
{
	char	*expanded;
	char	*tmp;
	char	*tmp2;

	expanded = ft_itoa(g_signal);
	tmp = ft_substr(str, 0, i);
	tmp2 = ft_strjoin(tmp, expanded);
	free(tmp);
	free(expanded);
	if (!tmp2)
		return ;
	expanded = ft_strjoin(tmp2, ft_substr(str, i + 2, ft_strlen(str) - i - 2));
	free(tmp2);
	free(str);
	if (!expanded)
		return ;
	str = ft_strdup(expanded);
	token->length = ft_strlen(str);
	token->value = ft_strdup(str);
	free(expanded);
}

void	ft_expand_token(t_subcommand *subcommand, t_token *token)
{
	char	limiter;
	char	*expanded;
	char	*str;
	int		i;

	while (token)
	{
		i = 0;
		limiter = '\0';
		str = ft_substr(token->value, 0, token->length);
		while (str[i])
		{
			limiter = ft_type_token(str[i], limiter);
			if (str[i] == '$' && str[i + 1] == '?' && limiter != '\'')
				ft_is_exit_status(subcommand, token, str, i);
			if (str[i] == '$' && limiter != '\'')
			{
				expanded = ft_strjoin(ft_substr(str, 0, i),
						ft_expand_dollar(subcommand, str));
				if (!expanded)
					return free(str), (void)0;
				while (str[i] && str[i] != '?' && ft_is_valid_symbol(str[i])
					&& str[i + 1] != '\'' && str[i + 1] != '"' && !ft_isspace(str[i + 1]))
					++i;
				if (!str[i])
				{
					token->length = ft_strlen(expanded);
					token->value = ft_strdup(expanded);
					free(str);
					str = ft_strdup(expanded);
					break ;
				}
				free(str);
				str = ft_strjoin(expanded, ft_substr(token->value, i + 1,
							token->length - i - 1));
				if (!expanded)
					return free(expanded), (void)0;
				token->length = ft_strlen(str);
				token->value = ft_strdup(str);
			}
			i++;
		}
		token = token->next;
		free(str);
	}
}