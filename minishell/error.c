/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:38:24 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 15:38:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"
#include <unistd.h>

void	ft_error(char *message)
{
	ft_dprintf(STDERR_FILENO, "%s\n", message);
}