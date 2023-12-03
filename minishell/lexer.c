/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/11/27 10:28:15 by codespace        ###   ########.fr       */
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

/**
 * @brief The ft_clean_tokens function is used after the expander to remove
 * tokens which have a length of 0, as a result of the expander not being able
 * to expand the token.
 *
 * @param token
 */
bool	ft_clean_tokens(t_token **token)
{
	t_token	*tmp;

	if (*token && (*token)->length == 0 && !(*token)->next)
	{
		(free((void *)(*token)->value), free(*token));
		*token = NULL;
		return (false);
	}
	while (*token != NULL)
	{
		if ((*token)->length == 0)
		{
			tmp = *token;
			*token = (*token)->next;
			(free((void *)tmp->value), free(tmp));
		}
		else
			token = &(*token)->next;
	}
	return (true);
}

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

static bool	ft_handle_symbols(t_lexer *lexer, t_token *token)
{
	t_quote_state	state;

	if (!ft_is_valid_symbol(lexer->raw[lexer->cursor]))
		return (false);
	ft_init_state(&state, lexer->raw[lexer->cursor]);
	token->type = TOKEN_SYMBOL;
	while (lexer->cursor < lexer->length)
	{
		lexer->cursor++;
		token->length++;
		ft_modify_state(&state, lexer->raw[lexer->cursor]);
		if (state != STATE_DEFAULT && !lexer->raw[lexer->cursor + 1])
		{
			token->type = TOKEN_INVALID;
			token->value = lexer->raw + (lexer->cursor - token->length);
			return (token->length += 1, lexer->cursor += 1, true);
		}
		if (state == STATE_DEFAULT && lexer->raw[lexer->cursor] != '\0'
			&& !ft_is_valid_symbol(lexer->raw[lexer->cursor + 1]))
		{
			token->value = lexer->raw + (lexer->cursor - token->length);
			return (token->length += 1, lexer->cursor += 1, true);
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
