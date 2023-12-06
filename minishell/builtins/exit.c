/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:05:11 by codespace         #+#    #+#             */
/*   Updated: 2023/12/06 19:02:46 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../free.h"
#include "../token.h"
#include "../display.h"
#include "../history.h"
#include "../char.h"
#include "../str.h"
#include <unistd.h>

int	ft_parse_exit_code(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			if (__MACH__)
				return (255);
			return (2);
		}
		i++;
	}
	return (ft_atoi(str));
}

int	ft_exit(t_subcommand *subcommand, t_command *command)
{
	int	exit_value;

	exit_value = 0;
	if (subcommand->args[1] && subcommand->args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), EXIT_FAILURE);
	if (subcommand->args[1])
		exit_value = ft_parse_exit_code(subcommand->args[1]);
	ft_free_all(command, true);
	ft_history_clear();
	exit(exit_value % 256);
}
