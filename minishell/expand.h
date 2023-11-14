/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:37:29 by codespace         #+#    #+#             */
/*   Updated: 2023/11/13 15:27:36 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "structs.h"

void	ft_expand_token(t_subcommand *subcommand, t_token *token);
char	*ft_expand_dollar(t_subcommand *subcommand, char *str);
char	ft_type_token(char c, char type);
#endif