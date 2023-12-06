/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:13:35 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/06 10:49:19 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_check_pipe_valid(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE && !tokens->next)
			return (1);
		if (tokens->type == TOKEN_PIPE
			&& tokens->next && tokens->next->type == TOKEN_PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	ft_check_io_valid(t_token *token)
{
	while (token)
	{
		if (ft_is_io_symbol(token) && !token->next)
			return (1);
		if (ft_is_io_symbol(token)
			&& token->next && token->next->type != TOKEN_SYMBOL
			&& token->next->type != TOKEN_SQ && token->next->type != TOKEN_DQ)
			return (1);
		token = token->next;
	}
	return (0);
}
