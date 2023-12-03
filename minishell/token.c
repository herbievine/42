/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:00:30 by herbie            #+#    #+#             */
/*   Updated: 2023/12/03 08:01:30 by codespace        ###   ########.fr       */
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

bool	ft_free_tokens(t_token **tokens)
{
	t_token	*next;

	if (!tokens || !*tokens)
		return (false);
	while (*tokens)
	{
		next = (*tokens)->next;
		if ((*tokens)->value && (*tokens)->is_malloced)
			free((char *)(*tokens)->value);
		free(*tokens);
		*tokens = next;
	}
	*tokens = NULL;
	return (true);
}
