/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:14:02 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 15:48:10 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "mem.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_command	ft_command_new(void)
{
	t_command	command;

	command.tokens = NULL;
	command.token_length = 0;
	command.subcommands = NULL;
	command.subcommand_length = 0;
	return (command);
}
