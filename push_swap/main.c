/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:55:36 by herbie            #+#    #+#             */
/*   Updated: 2023/03/12 10:42:05 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "display.h"
#include "strings.h"
#include "utils.h"
#include "parse.h"
#include "split.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc == 1)
		return (0);
	args = ft_parse_args(argc, argv);
	if (
		!args
		|| ft_replace_args_by_indices(&(args->int_array), args->count) == -1
	)
		return (0);
	ft_sort_args(args->int_array, args->count);
	ft_free_args(args, true);
	return (0);
}
