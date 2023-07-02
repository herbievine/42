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
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>

void	ft_await_command_entry(void)
{
	char	*buffer;

	while (true)
	{
		buffer = readline("minishell> ");
		write(STDIN_FILENO, buffer, ft_strlen(buffer));
		free(buffer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	ft_await_command_entry();
	return (0);
}
