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

void	ft_await_command_entry(void)
{
	char	*buffer;

	write(1, "minishell> ", 11);
	while (ft_read(&buffer, STDIN_FILENO, '\n') > 0)
	{
		write(STDIN_FILENO, buffer, ft_strlen(buffer));
		free(buffer);
		write(1, "minishell> ", 11);
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
