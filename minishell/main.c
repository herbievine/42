/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/07/13 17:07:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "io.h"
#include "parse.h"
#include "structs.h"
#include "print.h"
#include "error.h"
#include "lexer.h"
#include "command.h"
#include "history.h"
#include "token.h"
#include "signals.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>

void	ft_build_command(char *buffer)
{
	int			token_length;
	t_lexer		lexer;
	t_token		token;
	t_token		*token_list;

	token_length = 0;
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	token_list = NULL;
	while (token.type != TOKEN_EOF)
	{
		if (token.type == TOKEN_INVALID)
		{
			ft_invalid_token(lexer, token);
			break ;
		}
		if (ft_append_token(&token_list, token))
			token_length++;
		token = ft_lexer_next(&lexer);
	}
	ft_debug_print_command(token_list, token_length);
	ft_clear_tokens(&token_list);
}

void	ft_await_command_entry(void)
{
	char	*buffer;

	while (true)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			ft_handle_ctrl_d();
		if (ft_strlen(buffer) > 0)
		{
			ft_history_add(buffer);
			ft_build_command(buffer);
		}
		free(buffer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_history_new();
	ft_signals_register();
	ft_await_command_entry();
	return (0);
}
