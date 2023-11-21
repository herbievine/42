/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:53:08 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 14:53:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../str.h"
#include "../display.h"

int	ft_echo(t_subcommand *subcommand, t_token *token)
{
	int	option;
	int	i;

	i = 0;
	option = 0;
	if (subcommand->args[0] && subcommand->args[1]
		&& ft_strncmp(subcommand->args[1], "-n", 2) == 0
		&& ft_strlen(subcommand->args[1]) == 2)
		option = 1;
	while (subcommand->args[++i])
	{
		ft_putstr_fd(subcommand->args[i], subcommand->out_fd);
		if (subcommand->args[i + 1])
			ft_putchar_fd(' ', subcommand->out_fd);
	}
	if (!option)
		ft_putchar_fd('\n', subcommand->out_fd);
	return (0);
}