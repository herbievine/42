/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/29 15:23:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"
#include "builtins_func.h"
# include <stdbool.h>

typedef struct s_builtin
{
	int		(*func)(t_subcommand *subcommand, t_token *token);
}	t_builtin;

bool	ft_builtin(t_subcommand *s_command, t_token *token, char ***envp);
bool	ft_if_builtin(char *cmd);
bool	ft_builtin_valid(t_token *token, t_subcommand *subcommand, char *cmd, char ***envp);

#endif