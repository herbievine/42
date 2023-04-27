/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/04/20 15:24:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"
#include "print.h"
#include "structs.h"
#include "io.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int	ft_err(char *err)
{
	ft_dprintf(2, "pipex: %s\n", err);
	exit(1);
	return (1);
}

void	ft_bash_not_found(char *cmd)
{
	ft_dprintf(2, "bash: %s: command not found\n", cmd);
}
