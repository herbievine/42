/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:55:36 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 21:19:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "display.h"
#include "strings.h"
#include "utils.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_args	*args;

	args = ft_parse_args(argc, argv);
	if (ft_replace_args_by_indices(&(args->args), args->argc) == -1)
		return (0);
	ft_sort_args(args->args, args->argc);
	free(args->args);
	return (0);
}
