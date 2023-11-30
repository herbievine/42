/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:08:55 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 10:08:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../structs.h"

int	ft_cd(t_subcommand *subcommand);
int	ft_echo(t_subcommand *subcommand);
int	ft_env(char **env);
int	ft_exit(t_subcommand *subcommand, t_token *token);
int	ft_export(t_subcommand *subcommand, t_token *token, char ***env);
int	ft_pwd(t_subcommand *subcommand);
int	ft_unset(t_subcommand *subcommand, char ***env);

#endif