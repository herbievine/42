/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/07/10 13:15:30 by herbie           ###   ########.fr       */
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

static bool	ft_handle_quotes(t_lexer *lexer, t_token *token)
{
	if (lexer->state == LEXER_STATE_IN_SQ || lexer->state == LEXER_STATE_IN_DQ)
	{
		token->type = TOKEN_SYMBOL;
		while (lexer->cursor < lexer->length)
		{
			if (lexer->state == LEXER_STATE_IN_SQ
				&& lexer->raw[lexer->cursor] == '\'')
				break ;
			else if (lexer->state == LEXER_STATE_IN_DQ
				&& lexer->raw[lexer->cursor] == '"')
				break ;
			if (!lexer->raw[lexer->cursor + 1])
			{
				token->type = TOKEN_INVALID;
				token->value = lexer->raw + (lexer->cursor - token->length);
				token->length = token->length + 1;
				lexer->cursor++;
				return (true);
			}
			lexer->cursor++;
			token->length++;
		}
		return (true);
	}
	return (false);
}

#define TOKEN_COUNT 7

static bool	ft_handle_tokens(t_lexer *lexer, t_token *token)
{
	int					i;
	t_bash_token_map	*token_map;

	i = -1;
	token_map = ft_get_token_map();
	if ((lexer->state == LEXER_STATE_IN_DQ
			&& lexer->raw[lexer->cursor] == '\'')
		|| (lexer->state == LEXER_STATE_IN_SQ
			&& lexer->raw[lexer->cursor] == '"'))
		return (false);
	while (++i < TOKEN_COUNT)
	{
		if (ft_strncmp(&lexer->raw[lexer->cursor],
				token_map[i].value, ft_strlen(token_map[i].value)) == 0)
		{
			ft_mutate_lexer_state(lexer);
			lexer->cursor += ft_strlen(token_map[i].value);
			token->type = token_map[i].type;
			token->length = ft_strlen(token_map[i].value);
			return (true);
		}
	}
	return (false);
}

t_lexer	ft_lexer_new(const char *raw)
{
	t_lexer	lexer;

	lexer.raw = raw;
	lexer.state = LEXER_STATE_DEFAULT;
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
	if (ft_handle_tokens(lexer, &token))
		return (token);
	if (ft_handle_quotes(lexer, &token))
		return (token);
	if (ft_handle_symbol(lexer, &token))
		return (token);
	lexer->cursor++;
	token.type = TOKEN_INVALID;
	token.length = 1;
	return (token);
}
