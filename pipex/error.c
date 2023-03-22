/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/03/22 11:11:29 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void error(char *err)
{
	if (errno)
		perror(err);
	else
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, "\n", 1);
	}
}