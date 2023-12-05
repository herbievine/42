/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:44:20 by codespace         #+#    #+#             */
/*   Updated: 2023/12/05 20:23:48 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	ft_signals_register(void);
void	ft_handle_ctrl_d(void);
void	ft_handle_nothing(int signal);
void	antislash(int sig);
void	ctrlc(int sig);

#endif /* SIGNALS_H */
