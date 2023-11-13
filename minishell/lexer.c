/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/11/13 14:49:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "char.h"
#include "structs.h"
#include "str.h"
#include <stdbool.h>
#include <stdio.h>

static bool	ft_handle_symbol(t_lexer *lexer, t_token *token)
{
	if (ft_is_valid_symbol(lexer->raw[lexer->cursor]))
	{
		token->type = TOKEN_SYMBOL;
		while (lexer->cursor < lexer->length
			&& (ft_is_valid_symbol(lexer->raw[lexer->cursor])))
		{
			lexer->cursor++;
			token->length++;
		}
		return (true);
	}
	return (false);
}

// Tokens are defined in `lexer_utils.c`
// consisting of <<, >>, <, > or |
#define TOKEN_COUNT 5

static bool	ft_handle_tokens(t_lexer *lexer, t_token *token)
{
	int					i;
	t_bash_token_map	*token_map;

	i = -1;
	token_map = ft_get_token_map();
	while (++i < TOKEN_COUNT)
	{
		if (ft_strncmp(&lexer->raw[lexer->cursor],
				token_map[i].value, ft_strlen(token_map[i].value)) == 0)
		{
			lexer->cursor += ft_strlen(token_map[i].value);
			token->type = token_map[i].type;
			token->length = ft_strlen(token_map[i].value);
			return (true);
		}
	}
	return (false);
}

#define SQ '\''
#define DQ '"'

static bool	ft_handle_quotes(t_lexer *lexer, t_token *token)
{
	char	state;

	if (lexer->raw[lexer->cursor] == SQ)
		state = SQ;
	else if (lexer->raw[lexer->cursor] == DQ)
		state = DQ;
	else
		return (false);
	token->type = TOKEN_SYMBOL;
	while (lexer->cursor < lexer->length)
	{
		lexer->cursor++;
		token->length++;
		if (!lexer->raw[lexer->cursor + 1]
			&& (state == SQ && lexer->raw[lexer->cursor] != SQ
				|| state == DQ && lexer->raw[lexer->cursor] != DQ))
		{
			token->type = TOKEN_INVALID;
			token->value = lexer->raw + (lexer->cursor - token->length);
			token->length = token->length + 1;
			lexer->cursor++;
			return (true);
		}
		if ((state == SQ && lexer->raw[lexer->cursor] == SQ)
			|| (state == DQ && lexer->raw[lexer->cursor] == DQ))
		{
			token->value = lexer->raw + (lexer->cursor - token->length);
			token->length++;
			lexer->cursor++;
			break ;
		}
	}
	return (true);
}

t_lexer	ft_lexer_new(const char *raw)
{
	t_lexer	lexer;

	lexer.raw = raw;
	lexer.length = ft_strlen(raw);
	lexer.cursor = 0;
	return (lexer);
}

t_token	ft_lexer_next(t_lexer *lexer)
{
	t_token	token;

	while (lexer->cursor < lexer->length
		&& ft_isspace(lexer->raw[lexer->cursor]))
		lexer->cursor++;
	token.value = &lexer->raw[lexer->cursor];
	token.length = 0;
	token.next = NULL;
	if (lexer->cursor >= lexer->length)
	{
		token.type = TOKEN_EOF;
		return (token);
	}
	if (ft_handle_quotes(lexer, &token))
		return (token);
	if (ft_handle_tokens(lexer, &token))
		return (token);
	if (ft_handle_symbol(lexer, &token))
		return (token);
	lexer->cursor++;
	token.type = TOKEN_INVALID;
	token.length = 1;
	return (token);
}
