/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:11 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/13 15:33:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "structs.h"

int		ft_echo(t_token *token, t_subcommand *subcommand);
bool	ft_is_antislash(char c, char type, int care_of_quote);

#endif