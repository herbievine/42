/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:49:53 by herbie            #+#    #+#             */
/*   Updated: 2023/03/12 10:42:05 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parse.h"
#include "strings.h"
#include "split.h"
#include "utils.h"
#include <stdio.h>
#include <limits.h>

t_args	*ft_parse_args(int argc, char **argv)
{
	int		i;
	t_args	*arg;

	if (argc == 2)
		arg = ft_get_args_from_str(argv[1]);
	else
		arg = ft_get_args_from_argv(argc, argv);
	ft_check_if_args_are_numbers(arg, arg->count);
	arg->int_array = malloc(sizeof(int) * (arg->count));
	if (!arg->int_array)
		return (
			ft_free_args(arg, false),
			ft_putstr_fd("Error\n", 2), exit(1), NULL);
	i = -1;
	while (++i < arg->count)
	{
		if (ft_atoi(arg->str_array[i]) > INT_MAX
			|| ft_atoi(arg->str_array[i]) < INT_MIN)
			return (
				ft_free_args(arg, true),
				ft_putstr_fd("Error\n", 2), exit(1), NULL);
		arg->int_array[i] = (int)ft_atoi(arg->str_array[i]);
	}
	ft_check_duplicates(arg);
	return (arg);
}

t_args	*ft_get_args_from_argv(int argc, char **argv)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (!arg)
		return (ft_putstr_fd("Error\n", 2), exit(1), NULL);
	arg->count = argc - 1;
	arg->str_array = argv + 1;
	arg->int_array = NULL;
	arg->is_str_array_alloced = false;
	return (arg);
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
	arg->count = i;
	arg->str_array = args;
	arg->int_array = NULL;
	arg->is_str_array_alloced = true;
	return (arg);
}

void	ft_check_if_args_are_numbers(t_args *arg, int count)
{
	int	i;

	while (count-- > 0)
	{
		i = 0;
		while (arg->str_array[count][i])
		{
			if (
				(i == 0 && arg->str_array[count][i] == '-')
				|| (i == 0 && arg->str_array[count][i] == '+')
			)
				i++;
			if (
				arg->str_array[count][i] >= 48
				&& arg->str_array[count][i] <= 57
			)
				i++;
			else
				return (
					ft_free_args(arg, false),
					ft_putstr_fd("Error\n", 2), exit(1));
		}
	}
}

void	ft_check_duplicates(t_args *arg)
{
	int	i;
	int	j;

	i = -1;
	while (++i < arg->count)
	{
		j = i;
		while (++j < arg->count)
		{
			if (arg->int_array[i] == arg->int_array[j] && i != j)
			{
				ft_free_args(arg, true);
				ft_putstr_fd("Error\n", 2);
				exit(1);
			}
		}
	}
}
