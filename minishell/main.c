/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/04/28 15:55:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "io.h"
#include "parse.h"
#include "structs.h"
#include "print.h"
#include "error.h"
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_await_command_entry(t_shell *shell)
{
	char		*buffer;
	t_command	*command;

	while (true)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		if (ft_strlen(buffer) > 0)
		{
			add_history(buffer);
			if (!ft_parse(shell, buffer))
				ft_error(ECMD);
			command = malloc(sizeof(t_command));
			if (!command)
				ft_error(EMALLOC);
			command->raw = ft_substr(buffer, 0, ft_strlen(buffer));
			shell->current = command;
			if (!ft_lexer(shell, buffer))
				ft_error(ECMD);
		}
		free(buffer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_await_command_entry(&shell);
	return (0);
}
