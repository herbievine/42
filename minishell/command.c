/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:14:02 by herbie            #+#    #+#             */
/*   Updated: 2023/12/04 19:47:56 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "mem.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

t_command	ft_command_new(char ***env)
{
	t_command	command;

	command.tokens = NULL;
	command.token_length = 0;
	command.subcommands = NULL;
	command.pid = NULL;
	command.prev_pipe_fd = -1;
	command.pipe_fd[READ] = -1;
	command.pipe_fd[WRITE] = -1;
	command.subcommand_length = 0;
	command.env = env;
	return (command);
}
