/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/12/05 15:50:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "parse.h"
#include "structs.h"
#include "print.h"
#include "error.h"
#include "lexer.h"
#include "command.h"
#include "subcommand.h"
#include "history.h"
#include "token.h"
#include "signals.h"
#include "free.h"
#include "mem.h"
#include "process.h"
#include "expand.h"
#include "env.h"
#include "builtin.h"
#include "quotes.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

int	g_signal = 0;

static void	ft_execution_wrapper(t_command *command)
{
	int	retval;

	retval = -1;
	command->pid = ft_calloc(sizeof(pid_t), command->subcommand_length);
	if (!command->pid)
		g_signal = 1;
	retval = ft_execute(command, command->env);
	if (retval != -1)
		g_signal = retval;
}

static bool	ft_parse_wrapper(t_command *command)
{
	if (command->token_length == 0 || !command->tokens)
		return (false);
	ft_expand_token(command->subcommands, command->tokens);
	ft_suppress_quotes(command->subcommands, command->tokens);
	if (!ft_clean_tokens(&command->tokens))
		return (false);
	if (!ft_parse(command->tokens, command->subcommands, command->env))
		return (false);
	return (true);
}

static void	ft_build_command(char *buffer, char ***env)
{
	t_command	command;
	t_lexer		lexer;
	t_token		token;

	command = ft_command_new(env);
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	while (token.type != TOKEN_EOF)
	{
		if (token.type == TOKEN_INVALID)
			return (ft_free_tokens(&command.tokens),
				ft_invalid_token(lexer, token), g_signal = 1, (void)0);
		if (!ft_append_token(&command.tokens, token))
			return (ft_free_tokens(&command.tokens), g_signal = 1, (void)0);
		command.token_length++;
		token = ft_lexer_next(&lexer);
	}
	if (!ft_create_subcommands(&command, *env))
		return (ft_free_all(&command, false));
	if (!ft_parse_wrapper(&command))
		return (ft_free_all(&command, false));
	ft_execution_wrapper(&command);
	ft_free_all(&command, false);
}

void	ft_await_command_entry(char ***env)
{
	char	*buffer;

	while (true)
	{
		ft_signals_register();
		buffer = readline("minishell> ");
		if (!buffer)
		{
			ft_free_array(*env, -1);
			ft_handle_ctrl_d();
		}
		if (ft_strlen(buffer) > 0)
		{
			ft_history_add(buffer);
			ft_build_command(buffer, env);
		}
		free(buffer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	g_signal = 0;
	env = ft_env_init(envp);
	if (!env)
		return (1);
	ft_history_new();
	ft_await_command_entry(&env);
	return (0);
}
