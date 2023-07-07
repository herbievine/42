/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/07/07 16:53:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "char.h"
#include "structs.h"
#include "str.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_bash_token_map
{
	char			*value;
	t_token_types	type;
}	t_bash_token_map;

static void	ft_trim_left(t_lexer *lexer)
{
	while (lexer->cursor < lexer->length
		&& ft_isspace(lexer->raw[lexer->cursor]))
		lexer->cursor++;
}

static bool	ft_handle_symbol(t_lexer *lexer, t_token *token)
{
	if (ft_isalnum(lexer->raw[lexer->cursor])
		|| lexer->raw[lexer->cursor] == '-')
	{
		token->type = TOKEN_SYMBOL;
		while (lexer->cursor < lexer->length
			&& (ft_isalnum(lexer->raw[lexer->cursor])
				|| lexer->raw[lexer->cursor] == '-'))
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
			if (LEXER_STATE_IN_SQ && lexer->raw[lexer->cursor] == '\'')
				break ;
			else if (LEXER_STATE_IN_DQ && lexer->raw[lexer->cursor] == '"')
				break ;
			if (!lexer->raw[lexer->cursor + 1])
			{
				token->type = TOKEN_INVALID;
				token->value = lexer->raw[lexer->cursor - token->length];
				token->length = token->length + 2;
				return (true);
			}
			lexer->cursor++;
			token->length++;
		}
		return (true);
	}
	return (false);
}

static bool	ft_handle_tokens(t_lexer *lexer, t_token *token)
{
	int						i;
	const t_bash_token_map	token_map[] = {
	{
		.value = ">>",
		.type = TOKEN_GT_GT,
	},
	{
		.value = "<<",
		.type = TOKEN_LT_LT,
	},
	{
		.value = ">",
		.type = TOKEN_GT,
	},
	{
		.value = "<",
		.type = TOKEN_LT,
	},
	{
		.value = "|",
		.type = TOKEN_PIPE,
	},
	{
		.value = "'",
		.type = TOKEN_SQ,
	},
	{
		.value = "\"",
		.type = TOKEN_DQ,
	}
	};

	i = -1;
	while (++i < sizeof(token_map) / sizeof(t_bash_token_map))
	{
		if (ft_strncmp(&lexer->raw[lexer->cursor],
				token_map[i].value, ft_strlen(token_map[i].value)) == 0)
		{
			if (lexer->raw[lexer->cursor] == '\''
				&& lexer->state == LEXER_STATE_DEFAULT)
				lexer->state = LEXER_STATE_IN_SQ;
			else if (lexer->raw[lexer->cursor] == '\''
				&& lexer->state == LEXER_STATE_IN_SQ)
				lexer->state = LEXER_STATE_DEFAULT;
			else if (lexer->raw[lexer->cursor] == '"'
				&& lexer->state == LEXER_STATE_DEFAULT)
				lexer->state = LEXER_STATE_IN_DQ;
			else if (lexer->raw[lexer->cursor] == '"'
				&& lexer->state == LEXER_STATE_IN_DQ)
				lexer->state = LEXER_STATE_DEFAULT;
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
	int						i;
	t_token					token;

	ft_trim_left(lexer);
	token.value = &lexer->raw[lexer->cursor];
	token.length = 0;
	if (lexer->cursor >= lexer->length)
	{
		token.type = TOKEN_END;
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

// void	ft_lexer_skip_whitespace(t_lexer *lexer)
// {
// 	while (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n')
// 		ft_lexer_advance(lexer);
// }

// t_token	*ft_lexer_get_next_token(t_lexer *lexer)
// {
// 	while (lexer->c != '\0' && lexer->i < lexer->len)
// 	{
// 		if (lexer->c == ' ' || lexer->c == '\t' || lexer->c == '\n')
// 			ft_lexer_skip_whitespace(lexer);
// 		if (lexer->c == '"')
// 			return (ft_lexer_collect_string(lexer));
// 	}
// 	return (NULL);
// }

// t_token	*ft_lexer_collect_string(t_lexer *lexer)
// {
// 	t_token	*token;
// 	int		start;
// 	int		end;

// 	ft_lexer_advance(lexer);
// 	start = lexer->i;
// 	while (lexer->c != '"')
// 		ft_lexer_advance(lexer);
// 	end = lexer->i;
// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->type = TOKEN_LITERAL;
// 	token->value = ft_substr(lexer->raw, start, end - start);
// 	return (token);
// }