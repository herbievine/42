/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:24:23 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 10:24:23 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"
#include "structs.h"
#include "free.h"
#include <stdlib.h>

void	ft_err(char *msg, t_map *map)
{
	ft_dprintf(2, "Error\n%s\n", msg);
	if (map)
		ft_free_map(map);
	exit(1);
}
