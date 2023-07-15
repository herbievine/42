/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:00:30 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 13:15:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "structs.h"
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int	ft_find_next_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (i);
		token = token->next;
		i++;
	}
	return (-1);
}

bool	ft_append_token(t_token **tokens, t_token token)
{
	t_token	*head;
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	ft_memcpy(new_token, &token, sizeof(t_token));
	if (!*tokens)
		*tokens = new_token;
	else
	{
		head = *tokens;
		while ((*tokens)->next)
			*tokens = (*tokens)->next;
		(*tokens)->next = new_token;
		*tokens = head;
	}
	return (true);
}

bool	ft_clear_tokens(t_token **tokens)
{
	t_token	*next;

	while (*tokens)
	{
		next = (*tokens)->next;
		free(*tokens);
		*tokens = next;
	}
	*tokens = NULL;
	return (true);
}
