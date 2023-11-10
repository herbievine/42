/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:48 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/10 16:56:06 by juliencros       ###   ########.fr       */
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
char	**ft_add_cpy_env_var(char *key, char *value, char ***envp);
void	ft_change_exit_status(char ***envp);
char	**ft_create_cpy_var(char *key, char *value, char ***envp, int i);

#endif