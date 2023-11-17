/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:07:23 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/17 10:42:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "str.h"
#include "display.h"

int	ft_echo(t_token *token, t_subcommand *subcommand)
{
	int	option;
	int	i;

	i = 0;
	option = 0;
	if (subcommand->args[0] && subcommand->args[1]
		&& ft_strncmp(subcommand->args[1], "-n", 2) == 0
		&& ft_strlen(subcommand->args[1]) == 2)
		option = 1;
	while (subcommand)
	{
		while (subcommand->args[++i])
		{
			ft_putstr_fd(subcommand->args[i], subcommand->out_fd);
			if (subcommand->args[i + 1])
				ft_putchar_fd(' ', subcommand->out_fd);
		}
		subcommand = subcommand->next;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (0);
}
