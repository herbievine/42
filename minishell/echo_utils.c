/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:20:01 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/11 10:00:37 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	ft_type_token(t_token *token, int type)
{
	if (token->type == TOKEN_SQ && type != TOKEN_SQ)
		return (type = TOKEN_SQ);
	else if (token->type == TOKEN_DQ && type != TOKEN_DQ)
		return (type = TOKEN_DQ);
	else if (token->type == TOKEN_SQ && type == TOKEN_SQ)
		return (type = 2);
	else if (token->type == TOKEN_DQ && type == TOKEN_DQ)
		return (type = 2);
	return (type);
}

bool	ft_is_antislash(char c, int type, int care_of_quote)
{
	if (care_of_quote == 1)
	{
		if (type == TOKEN_DQ && c == '\'')
			return (false);
		if (type == TOKEN_SQ && c == '\"')
			return (false);
	}
	if (c == '\\' || c == '\'' || c == '\"' || c == '\n'
		|| c == '\t' || c == '\v' || c == '\b'
		|| c == '\r' || c == '\f' || c == '\a')
		return (true);
	return (false);
}
