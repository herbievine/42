/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:13 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 18:24:22 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "structs.h"
#include "str.h"
#include <stdbool.h>

void	ft_handle_literals(t_command *command, char *cursor)
{

}

t_token	ft_handle_redirects(t_command *command, char *cursor)
{
	if (cursor[0] == '>')
	{
		if (cursor[1] == '>')
			return (TOKEN_GREATER_GREATER);
		else
			return (TOKEN_GREATER);
	}
	else if (cursor[0] == '<')
	{
		if (cursor[1] == '<')
			return (TOKEN_LESSER_LESSER);
		else
			return (TOKEN_LESSER);
	}
	return (NULL);
}

void	ft_handle_miscs(t_command *command, char *cursor)
{

}

t_token	ft_get_next_token(const char *raw, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			return (TOKEN_PIPE);
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				return (TOKEN_GREATER_GREATER);
			else
				return (TOKEN_GREATER);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				return (TOKEN_LESSER_LESSER);
			else
				return (TOKEN_LESSER);
		}
	}
	return (NULL);
}

bool	ft_lexer(t_shell *shell)
{
	int			i;
	t_list	*head;

	i = 0;
	while (shell->current->raw)
	{
		if (shell->current->raw[i] == '<' || shell->current->raw[i] == '>')
			ft_handle_redirects(shell->current, shell->current->raw + i);
	}

}
