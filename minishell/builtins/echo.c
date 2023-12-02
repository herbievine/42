/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:53:08 by codespace         #+#    #+#             */
/*   Updated: 2023/12/02 21:24:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../str.h"
#include "../display.h"
#include "../error.h"
#include <stdio.h>

static bool	is_newline_flag(char *arg);

int	ft_echo(t_subcommand *subcommand)
{
	char	**args;
	bool	print_newline;
	int		i;

	args = subcommand->args;
	print_newline = true;
	i = 0;
	while (args[++i] && is_newline_flag(args[i]))
		print_newline = false;
	while (args[i - 1] && args[i])
	{
		ft_putstr_fd(args[i], subcommand->out_fd);
		if (args[++i])
			ft_putchar_fd(' ', subcommand->out_fd);
	}
	if (print_newline)
		ft_putchar_fd('\n', subcommand->out_fd);
	return (0);
}

static bool	is_newline_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 0;
	while (arg[++i])
		if (arg[i] != 'n')
			return (false);
	return (true);
}
