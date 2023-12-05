/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/12/05 20:52:35 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "char.h"
#include "structs.h"
#include "str.h"
#include <stdbool.h>
#include <stdio.h>

// Tokens are defined in `lexer_utils.c`
// They consist of <<, >>, <, > or |
#define TOKEN_COUNT 5

static bool	ft_handle_tokens(t_lexer *l, t_token *t)
{
	int					i;
	t_bash_token_map	*token_map;

	i = -1;
	token_map = ft_get_token_map();
	while (++i < TOKEN_COUNT)
	{
		if (ft_strncmp(&l->raw[l->cursor],
				token_map[i].value, ft_strlen(token_map[i].value)) == 0)
		{
			l->cursor += ft_strlen(token_map[i].value);
			t->type = token_map[i].type;
			t->length = ft_strlen(token_map[i].value);
			return (true);
		}
	}
	return (false);
}

static bool	ft_check_exit_condition_symbols(t_lexer *l,
	t_token *t, t_quote_state	state)
{
	if (state == STATE_DEFAULT && t->length == 1
		&& !ft_is_valid_symbol(l->raw[l->cursor]))
	{
		t->value = l->raw + (l->cursor - t->length);
		return (true);
	}
	if (state != STATE_DEFAULT && !l->raw[l->cursor])
		return (t->type = TOKEN_INVALID, false);
	if (state != STATE_DEFAULT && !l->raw[l->cursor + 1])
	{
		t->type = TOKEN_INVALID;
		t->value = l->raw + (l->cursor - t->length);
		return (t->length += 1, l->cursor += 1, true);
	}
	if (state == STATE_DEFAULT && l->raw[l->cursor] != '\0'
		&& !ft_is_valid_symbol(l->raw[l->cursor + 1]))
	{
		t->value = l->raw + (l->cursor - t->length);
		return (t->length += 1, l->cursor += 1, true);
	}
	return (false);
}

static bool	ft_handle_symbols(t_lexer *l, t_token *t)
{
	t_quote_state	state;

	if (!ft_is_valid_symbol(l->raw[l->cursor]))
		return (false);
	ft_init_state(&state, l->raw[l->cursor]);
	t->type = TOKEN_SYMBOL;
	while (l->cursor < l->length)
	{
		l->cursor++;
		t->length++;
		ft_modify_state(&state, l->raw[l->cursor]);
		if (ft_check_exit_condition_symbols(l, t, state))
			return (true);
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

/**
 * @brief The ft_lexer_next function 
 * 
 * @param lexer 
 * @return t_token 
 */
t_token	ft_lexer_next(t_lexer *lexer)
{
	t_token	token;

	while (lexer->cursor < lexer->length
		&& ft_isspace(lexer->raw[lexer->cursor]))
		lexer->cursor++;
	token.value = &lexer->raw[lexer->cursor];
	token.length = 0;
	token.next = NULL;
	token.is_malloced = false;
	if (lexer->cursor >= lexer->length)
		return (token.type = TOKEN_EOF, token);
	if (ft_handle_tokens(lexer, &token))
		return (token);
	if (ft_handle_symbols(lexer, &token))
		return (token);
	lexer->cursor++;
	token.type = TOKEN_INVALID;
	token.length = 1;
	return (token);
}
