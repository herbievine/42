/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/07/07 16:41:52 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "io.h"
#include "parse.h"
#include "structs.h"
#include "print.h"
#include "error.h"
#include "lexer.h"
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

void _debug_print_token(t_token token)
{
	printf(TOKEN_FMT, token.type, token.length, token.value);
}

void _debug_print_state(t_lexer lexer, t_token token)
{
	if (lexer.state == LEXER_STATE_DEFAULT)
		printf("DFLT | ");
	else if (lexer.state == LEXER_STATE_IN_SQ)
		printf("SIGL | ");
	else if (lexer.state == LEXER_STATE_IN_DQ)
		printf("DOUB | ");
	printf("%.*s\n", token.length, token.value);
}

void ft_await_command_entry(void)
{
	char *buffer;
	t_lexer lexer;
	t_token token;

	while (true)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break;
		if (ft_strlen(buffer) > 0)
		{
			add_history(buffer);
			lexer = ft_lexer_new(buffer);
			token = ft_lexer_next(&lexer);
			while (token.type != TOKEN_END)
			{
				// printf("\n\n");
				// sleep(1);
				_debug_print_token(token);
				// _debug_print_state(lexer, token);
				if (token.type == TOKEN_INVALID)
				{
					ft_invalid_token(lexer, token);
					break ;
				}
				token = ft_lexer_next(&lexer);
			}
		}
		free(buffer);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_await_command_entry();
	return (0);
}
