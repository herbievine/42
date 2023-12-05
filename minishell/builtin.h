/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 20:11:48 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"
# include <stdbool.h>

typedef struct s_builtin
{
	int		(*func)(t_subcommand *subcommand, t_token *token);
}	t_builtin;

bool	ft_builtin(t_subcommand *s_command, t_token *token, char ***envp);
bool	ft_if_builtin(char *cmd);
int		ft_builtin_valid(t_token *token, t_subcommand *subcommand,
			char *cmd, char ***envp, t_command *command);

#endif