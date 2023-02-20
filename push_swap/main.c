/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:55:36 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 22:07:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "display.h"
#include "strings.h"
#include "sort.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	*args;
	int size;

	args = ft_parse_args(argc, argv);
	size = argc - 1;
	ft_replace_args_by_indices(&args, size);
	ft_sort_large_array(args, size);
	free(args);
	return (0);
}

// int i = 0;
// int a[5] = {0, 3, 1, 4, 2};
// int b[5] = {};

// while (i < 5)
// {
// 	if ((a[i] >> 0) & 1)
// 		b[i] = a[i];
// 	i++;
// }

// i = 0;

// while (i < 5)
// {
// 	printf("%d\n ", b[i]);
// 	i++;
// }