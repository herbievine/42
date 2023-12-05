/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:44:18 by codespace         #+#    #+#             */
/*   Updated: 2023/12/05 20:31:33 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "print.h"
#include "history.h"
#include "display.h"
#include "structs.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	ft_handle_ctrl_c(int signal);
static void	ft_handle_ctrl_slash(int signal);

void	ft_signals_register(void)
{
	signal(SIGINT, &ft_handle_ctrl_c);
	signal(SIGQUIT, &ft_handle_ctrl_slash);
}

void	ft_handle_nothing(int signal)
{
	(void)signal;
	printf("\n");
}

void	ft_handle_ctrl_d(void)
{
	printf("exit\n");
	ft_history_clear();
	exit(EXIT_SUCCESS);
}

static void	ft_handle_ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	g_signal = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	ft_handle_ctrl_slash(int signal)
{
	(void)signal;
	rl_clear_visible_line();
	rl_reset_line_state();
	rl_redisplay();
}

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