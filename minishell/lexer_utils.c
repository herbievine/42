/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:52:58 by herbie            #+#    #+#             */
/*   Updated: 2023/07/07 21:52:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "structs.h"
#include "char.h"
#include <stdbool.h>

void	ft_mutate_lexer_state(t_lexer *lexer)
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
}

t_bash_token_map	*ft_get_token_map(void)
{
	static t_bash_token_map	map[7];

	map[0] = (t_bash_token_map){.value = ">>", .type = TOKEN_GT_GT};
	map[1] = (t_bash_token_map){.value = "<<", .type = TOKEN_LT_LT};
	map[2] = (t_bash_token_map){.value = ">", .type = TOKEN_GT};
	map[3] = (t_bash_token_map){.value = "<", .type = TOKEN_LT};
	map[4] = (t_bash_token_map){.value = "|", .type = TOKEN_PIPE};
	map[5] = (t_bash_token_map){.value = "'", .type = TOKEN_SQ};
	map[6] = (t_bash_token_map){.value = "\"", .type = TOKEN_DQ};
	return ((void *)map);
}

bool	ft_is_valid_symbol(char c)
{
	if (ft_isalnum(c) || c == '-' || c == '$' || c == '_' || c == '.'
		|| c == '/' || c == '~' || c == '*' || c == '!' || c == '?')
		return (true);
	return (false);
}
