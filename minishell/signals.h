/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:44:20 by codespace         #+#    #+#             */
/*   Updated: 2023/12/02 14:56:00 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	ft_signals_register(void);
void	ft_handle_ctrl_d(void);
void	ft_handle_nothing(int signal);

#endif /* SIGNALS_H */
