/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/11/27 10:25:50 by codespace        ###   ########.fr       */
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
		&& str[i + length] != '\'' && str[i + length] != '"'
		&& str[i + length] != '$')
		length++;
	if (length == 1)
		return (ft_strdup("$"));
	if (str[i + 1] == '?')
		length = 2;
	key = ft_substr(str, i + 1, length - 1);
	if (!key)
		return (subcommand->is_executable = false, g_signal = 1, NULL);
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

char	*ft_iter_in_string(t_subcommand *subcommand, char *str)
{
	int		i;
	char	limiter;

	i = 0;
	limiter = '\0';
	while (str[i])
	{
		limiter = ft_type_token(str[i], limiter);
		if (str[i] && ft_check_validity(str, i, limiter))
		{
			if (str[i] == '$' && str[i + 1] == '?')
			{
				i += ft_handle_exit_status(&str, i);
				continue ;
			}
			i = ft_expand_string(subcommand, &str, i);
			if (i == -1)
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}

void	ft_expand_token(t_subcommand *subcommand, t_token *token)
{
	char	*str;

	while (token)
	{
		str = ft_substr(token->value, 0, token->length);
		if (!str)
			return (subcommand->is_executable = false, g_signal = 1, (void)0);
		str = ft_iter_in_string(subcommand, str);
		if (!str)
			return (subcommand->is_executable = false, g_signal = 1, (void)0);
		if (token->value && token->is_malloced)
			free((char *)token->value);
		token->length = ft_strlen(str);
		token->value = ft_strdup(str);
		token->is_malloced = true;
		if (!token->value)
			return (subcommand->is_executable = false,
				g_signal = 1, (void)0);
		token = token->next;
		free(str);
	}
}
