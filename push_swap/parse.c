/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:49:53 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 11:50:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "strings.h"

int	*ft_parse_args(int argc, char **argv)
{
	int	i;
	int	*args;

	i = -1;
	args = malloc(sizeof(int) * (argc - 1));
	while (++i < argc - 1)
		args[i] = ft_atoi(argv[i + 1]);
	return (args);
}
