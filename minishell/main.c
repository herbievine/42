/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/11/14 13:58:13 by herbie           ###   ########.fr       */
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
#include "subcommand.h"
#include "history.h"
#include "token.h"
#include "signals.h"
#include "free.h"
#include "mem.h"
#include "process.h"
#include "check_subcommands.h"
#include "expand.h"
#include "env.h"
#include "builtin.h"
#include "quotes.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

int	g_signal;

#define SUBCOMMAND_FMT \
	"Subcommand(in_fd=%d, out_fd=%d, path='%s', \
	builtin=%d, mode=%d, is_heredoc=%d)\n"
#define SUBCOMMAND_ARG(subcommand)                      \
	subcommand.in_fd, subcommand.out_fd, subcommand.path, \
			subcommand.builtin, subcommand.mode, subcommand.is_heredoc

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

void	ft_build_command(char *buffer, char ***env)
{
	t_command	command;
	t_lexer		lexer;
	t_token		token;
	int 		return_value;

	return_value = -1;
	command = ft_command_new();
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	while (token.type != TOKEN_EOF)
	{
		// TODO move to parser
		if (token.type == TOKEN_INVALID)
		{
			ft_invalid_token(lexer, token);
			ft_clear_tokens(&command.tokens);
			g_signal = 1;
			*env = ft_env_set(*env, "?", "1");
			return ;
		}
		if (ft_append_token(&command.tokens, token))
			command.token_length++;
		token = ft_lexer_next(&lexer);
	}
	if (ft_create_subcommands(&command, *env))
	{
		ft_expand_token(command.subcommands, command.tokens);
		ft_suppress_quotes(command.subcommands, command.tokens);
		// ft_print_tokens(command.tokens);
		if (ft_parse(command.tokens, command.subcommands, env))
		{
			if (ft_check_subcommands(command.subcommands, command.tokens))
				return_value =  ft_execute(command.subcommands, &command.tokens);
			if (return_value != -1)
				g_signal = return_value;
		}
	}
	*env = ft_env_set(*env, "?", ft_itoa(g_signal));
	ft_free_subcommands(command.subcommands);
	ft_clear_tokens(&command.tokens);
}

void	ft_await_command_entry(char ***env)
{
	char	*buffer;

	while (true)
	{
		buffer = readline("minishell> ");
		if (!buffer)
		{
			ft_handle_ctrl_d();
			ft_free_array(*env, -1);
		}
		if (ft_strlen(buffer) > 0)
		{
			ft_history_add(buffer);
			ft_build_command(buffer, env);
		}
		free(buffer);
	}
	ft_free_array(*env, -1);
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
	printf("env: %p\n", env);
	ft_history_new();
	ft_signals_register();
	ft_await_command_entry(&env);
	return (0);
}
