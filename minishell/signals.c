/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:44:18 by codespace         #+#    #+#             */
/*   Updated: 2023/12/05 22:27:59 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "print.h"
#include "history.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
