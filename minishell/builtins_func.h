/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:58:17 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/22 14:25:57 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_FUNC_H
# define BUILTINS_FUNC_H

# include "structs.h"

int		ft_echo(t_subcommand *subcommand, t_token *token);
int		ft_export(t_subcommand *subcommand);
int		ft_env(t_subcommand *subcommand);
int		ft_unset(t_subcommand *subcommand);
int		ft_pwd(t_subcommand *subcommand);
int		ft_cd(t_subcommand *subcommand);
int		ft_exit(t_subcommand *subcommand);
#endif