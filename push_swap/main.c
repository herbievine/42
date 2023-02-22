/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:55:36 by herbie            #+#    #+#             */
/*   Updated: 2023/02/22 08:54:23 by herbie           ###   ########.fr       */
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

	if (argc == 1)
		return (0);
	args = ft_parse_args(argc, argv);
	if (
		!args
		|| ft_replace_args_by_indices(&(args->int_array), args->count) == -1
	)
		return (0);
	ft_sort_args(args->int_array, args->count);
	free(args->int_array);
	if (args->is_malloced)
		ft_free_list(args->str_array, args->count);
	free(args);
	return (0);
}
