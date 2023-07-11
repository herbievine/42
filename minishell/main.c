/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/07/10 13:15:30 by herbie           ###   ########.fr       */
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
#include "signals.h"
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>

void	ft_build_command(char *buffer)
{
	t_command	command;
	t_lexer		lexer;
	t_token		token;

	command = ft_command_new(buffer);
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	while (token.type != TOKEN_EOF)
	{
		if (token.type == TOKEN_INVALID)
		{
			ft_invalid_token(lexer, token);
			break ;
		}
		ft_append_token(&command, token);
		token = ft_lexer_next(&lexer);
	}
	ft_debug_print_command(command);
	ft_clear_tokens(&command);
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
