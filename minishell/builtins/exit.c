/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:05:11 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 11:05:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "../structs.h"
#include "../free.h"
#include "../token.h"
#include "../display.h"
#include "../history.h"
#include "../char.h"
#include "../str.h"

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
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			if (__MACH__)
				return (255);
			return (2);
		}
		i++;
	}
	return (ft_atoi(str));
}

int	ft_exit(t_subcommand *subcommand, t_token *token)
{
	int	i;
	int	exit_value;

	i = -1;
	exit_value = 0;

	if (subcommand->args[1] && subcommand->args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), 127);
	if (subcommand->args[1])
		exit_value = ft_parse_exit_code(subcommand->args[1]);
	ft_clear_tokens(&token);
	ft_free_array(subcommand->envp, -1);
	ft_free_subcommands(subcommand);
	ft_history_clear();
	exit(exit_value % 256);
}