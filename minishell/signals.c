/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:44:18 by codespace         #+#    #+#             */
/*   Updated: 2023/07/11 11:44:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "print.h"
#include "history.h"
#include "display.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// static void	ft_handle_ctrl_c(int signal);
static void	ft_handle_ctrl_slash(int signal);

// signal(SIGINT, &ft_handle_ctrl_c);
void	ft_signals_register(void)
{
	signal(SIGQUIT, &ft_handle_ctrl_slash);
}

void	ft_handle_ctrl_d(void)
{
	printf("exit\n");
	ft_history_clear();
	exit(EXIT_SUCCESS);
}

// static void	ft_handle_ctrl_c(int signal)
// {
// 	(void)signal;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_redisplay();
// }

static void	ft_handle_ctrl_slash(int signal)
{
	(void)signal;
	rl_clear_visible_line();
	rl_reset_line_state();
	rl_redisplay();
}
