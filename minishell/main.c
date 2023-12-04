/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/12/03 16:46:58 by juliencros       ###   ########.fr       */
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

#define SUBCOMMAND_FMT \
	"Subcommand(in_fd=%d, out_fd=%d, path='%s', \
	builtin=%d, mode=%d, is_heredoc=%d, is_executable=%d) and prev = '%s'\n"
#define SUBCOMMAND_ARG(subcommand)                      \
	subcommand.in_fd, subcommand.out_fd, subcommand.path, \
			subcommand.builtin, subcommand.mode, subcommand.is_heredoc, \
			subcommand.is_executable, subcommand.prev ? subcommand.prev->path : "NULL"

void	ft_print_tokens(t_token *tokens)
{
	t_token	*tmp;
	char	*str;

	tmp = tokens;
	while (tmp)
	{
		str = ft_substr(tmp->value, 0, tmp->length);
		printf("token: %s\t| type: %d\t| len:%d\n", str, tmp->type, tmp->length);
		free(str);
		tmp = tmp->next;
	}
}

void	ft_print_subcommands(t_command *command)
{
	t_subcommand	*subcommand;
	t_subcommand	tmp;
	int				i;

	subcommand = command->subcommands;
	while (subcommand)
	{
		ft_memcpy(&tmp, subcommand, sizeof(t_subcommand));
		printf(SUBCOMMAND_FMT, SUBCOMMAND_ARG(tmp));
		if (subcommand->args)
		{
			i = 0;
			while (subcommand->args[i])
			{
				printf("args[%d] = %s\n", i, subcommand->args[i]);
				i++;
			}
		}
		else
			printf("args = NULL\n");
		subcommand = subcommand->next;
	}
}

void	ft_fill_subcommand(t_command command, char ***env)
{
	int	retval;

	retval = -1;
	ft_expand_token(command.subcommands, command.tokens);
	ft_suppress_quotes(command.subcommands, command.tokens);
	ft_clean_tokens(&command.tokens);
	if (command.tokens
		&& ft_parse(command.tokens, command.subcommands, env))
	{
		// ft_print_subcommands(&command);
		retval = ft_execute(&command, env);
		if (retval != -1)
			g_signal = retval;
	}
}

void	ft_build_command(char *buffer, char ***env)
{
	t_command	command;
	t_lexer		lexer;
	t_token		token;

	command = ft_command_new();
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	while (token.type != TOKEN_EOF)
	{
		if (token.type == TOKEN_INVALID && ft_clear_tokens(&command.tokens))
			return (ft_invalid_token(lexer, token), g_signal = 1, (void)0);
		if (ft_append_token(&command.tokens, token))
			command.token_length++;
		else
			return (ft_clear_tokens(&command.tokens), g_signal = 1, (void)0);
		token = ft_lexer_next(&lexer);
	}
	if (ft_create_subcommands(&command, *env))
		ft_fill_subcommand(command, env);
	ft_free_subcommands(command.subcommands);
	ft_clear_tokens(&command.tokens);
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
