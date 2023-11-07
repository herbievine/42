/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:06:11 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/06 09:26:32 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "structs.h"

int		ft_echo(t_token *token, t_subcommand *subcommand);
bool	ft_is_antislash(char c, int type, int care_of_quote);
int		ft_type_token(t_token *token, int type);
bool	ft_is_antislash(char c, int type, int care_of_quote);

#endif