/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 21:52:58 by herbie            #+#    #+#             */
/*   Updated: 2023/11/12 08:58:08 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "structs.h"
#include "char.h"
#include <stdbool.h>

#define SQ '\''
#define DQ '"'

void	ft_modify_state(t_quote_state *state, char c)
{
	if (c == SQ && *state == STATE_DEFAULT)
		*state = STATE_IN_SQ;
	else if (c == DQ && *state == STATE_DEFAULT)
		*state = STATE_IN_DQ;
	else if (c == SQ && *state == STATE_IN_SQ)
		*state = STATE_DEFAULT;
	else if (c == DQ && *state == STATE_IN_DQ)
		*state = STATE_DEFAULT;
}

void	ft_init_state(t_quote_state *state, char c)
{
	if (c == SQ)
		*state = STATE_IN_SQ;
	else if (c == DQ)
		*state = STATE_IN_DQ;
	else
		*state = STATE_DEFAULT;
}

t_bash_token_map	*ft_get_token_map(void)
{
	static t_bash_token_map	map[5];

	map[0] = (t_bash_token_map){.value = ">>", .type = TOKEN_GT_GT};
	map[1] = (t_bash_token_map){.value = "<<", .type = TOKEN_LT_LT};
	map[2] = (t_bash_token_map){.value = ">", .type = TOKEN_GT};
	map[3] = (t_bash_token_map){.value = "<", .type = TOKEN_LT};
	map[4] = (t_bash_token_map){.value = "|", .type = TOKEN_PIPE};
	return ((void *)map);
}

bool	ft_is_valid_symbol(char c)
{
	if (ft_isalnum(c) || c == '-' || c == '$' || c == '='
		|| c == '_' || c == '.' || c == '/' || c == '~'
		|| c == '*' || c == '!' || c == '?' || c == '^'
		|| c == '+' || c == '"' || c == '\'')
		return (true);
	return (false);
}
