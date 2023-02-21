/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:49:53 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 21:24:34 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parse.h"
#include "strings.h"
#include "split.h"

// TODO remove this
#include <stdio.h>

t_args	*ft_parse_args(int argc, char **argv)
{
	int	i;
	t_args	*arg;

	if (argc == 2)
		arg = ft_get_args_from_str(argv[1]);
	else
		arg = ft_get_args_from_argv(argc, argv);
	ft_check_if_args_are_numbers(arg->argc, arg->argv);
	arg->args = malloc(sizeof(int) * (arg->argc));
	i= -1;
	while (++i < arg->argc)
		arg->args[i] = ft_atoi(arg->argv[i]);
	return (arg);
}

t_args	*ft_get_args_from_argv(int argc, char **argv)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (!arg)
		return (ft_putstr_fd("Error\n", 2), exit(1), NULL);
	arg->argc = argc - 1;
	arg->argv = argv + 1;
	arg->args = NULL;
	return arg;
}

t_args	*ft_get_args_from_str(char *str)
{
	char	**args;
	t_args	*arg;
	int		i;

	args = ft_split(str, ' ');
	if (!args)
		return (ft_putstr_fd("Error\n", 2), exit(1), NULL);
	arg = malloc(sizeof(t_args));
	if (!arg)
		return (ft_putstr_fd("Error\n", 2), exit(1), NULL);
	i = -1;
	while (args[++i])
		;
	arg->argc = i;
	arg->argv = args;
	arg->args = NULL;
	return arg;
}

void	ft_check_if_args_are_numbers(int argc, char **argv)
{
	int i;

	while (argc-- > 0)
	{
		i = 0;
		while (argv[argc][i])
		{
			if (i == 0 && (argv[argc][i] == '-' || argv[argc][i] == '+'))
				i++;
			if (argv[argc][i] >= 48 && argv[argc][i] <= 57)
				i++;
			else
			{
				ft_putstr_fd("Error\n", 2);
				exit(1);
			}
		}
	}
}
