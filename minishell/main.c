/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/11/07 14:39:29 by juliencros       ###   ########.fr       */
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
		printf("token: %s   |   type: %d\n", str, tmp->type);
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

void	ft_build_command(char *buffer, char **envp, char ***cpy_envp)
{
	t_command	command;
	t_lexer		lexer;
	t_token		token;

	command = ft_command_new();
	lexer = ft_lexer_new(buffer);
	token = ft_lexer_next(&lexer);
	while (token.type != TOKEN_EOF)
	{
		if (token.type == TOKEN_INVALID)
		{
			ft_invalid_token(lexer, token);
			ft_clear_tokens(&command.tokens);
			return ;
		}
		if (ft_append_token(&command.tokens, token))
			command.token_length++;
		token = ft_lexer_next(&lexer);
	}
	if (ft_create_subcommands(&command, envp, *cpy_envp))
	{
		// ft_print_subcommands(&command);
		// ft_print_tokens(command.tokens);
		if (ft_parse(command.tokens, command.subcommands, cpy_envp))
		{
			ft_expand_token(command.subcommands, command.tokens);
			if (ft_check_subcommands(command.subcommands, command.tokens))
			{
				ft_print_subcommands(&command);
				ft_exec_cmds(command.subcommands, &command.tokens);
			}
			ft_change_exit_status(command.subcommands);
		}
	}
	ft_free_subcommands(command.subcommands);
	ft_clear_tokens(&command.tokens);
}

void	ft_await_command_entry(char **envp)
{
	char	*buffer;
	char	**cpy_envp;

	cpy_envp = ft_cpy_env(envp);
	while (true)
	{
		buffer = readline("minishell> ");
		if (!buffer)
		{
			ft_handle_ctrl_d();
			ft_free_array(cpy_envp, -1);
		}
		if (ft_strlen(buffer) > 0)
		{
			ft_history_add(buffer);
			ft_build_command(buffer, envp, &cpy_envp);
		}
		free(buffer);
	}
	ft_free_array(cpy_envp, -1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_history_new();
	ft_signals_register();
	ft_await_command_entry(envp);
	return (0);
}
