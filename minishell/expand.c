/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:46 by codespace         #+#    #+#             */
/*   Updated: 2023/10/27 15:38:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "str.h"
#include "str2.h"
#include "env.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_expand_dollar(t_subcommand *subcommand, char *str)
{
	char	*expanded;
	char	*key;

	key = ft_substr(str, 1, ft_strlen(str) - 1);
	expanded = ft_get_cpy_env(subcommand, key);
	if (!expanded)
	{
		free(key);
		return (NULL);
	}
	return (free(key), expanded);
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
		}
		tokens = tokens->next;
		free(str);
	}
	return (true);
}
