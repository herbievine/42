/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:08:55 by codespace         #+#    #+#             */
/*   Updated: 2023/12/05 20:12:27 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../structs.h"

int	ft_cd(t_subcommand *subcommand);
int	ft_echo(t_subcommand *subcommand);
int	ft_env(char **env);
int	ft_exit(t_subcommand *subcommand, t_command *command);
int	ft_export(t_command *command, t_subcommand *subcommand, t_token *token);
int	ft_pwd(t_subcommand *subcommand);
int	ft_unset(t_command *command, t_subcommand *subcommand);

#endif