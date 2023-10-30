/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:48 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/28 08:09:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

char	*ft_get_cpy_env(t_subcommand *subcommand, char *key);
void	ft_set_cpy_env(t_subcommand *subcommand, char *key, char *value);
char	**ft_get_paths(t_subcommand *subcommand);
char	**ft_cpy_env(char **envp);
char	**ft_remove_cpy_env_var(char **cpy_envp, char *key);
void	ft_add_cpy_env_var(t_subcommand *subcommand, char *value);

#endif