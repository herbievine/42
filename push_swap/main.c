/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:55:36 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 22:08:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "display.h"
#include "strings.h"
#include "utils.h"
#include "parse.h"
#include "split.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_args	*args;

	args = ft_parse_args(argc, argv);
	if (!args || ft_replace_args_by_indices(&(args->args), args->argc) == -1)
		return (0);
	ft_sort_args(args->args, args->argc);
	free(args->args);
	if (argc == 2)
		ft_free_list(args->argv, args->argc);
	free(args);
	return (0);
}
