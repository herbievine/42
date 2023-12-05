/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:37:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/05 22:30:58 by herbie           ###   ########.fr       */
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

bool	ft_builtin(t_command *command, t_subcommand *subcommand,
			t_token *token);
bool	ft_if_builtin(char *cmd);
int		ft_builtin_valid(t_command *command, t_subcommand *subcommand,
			t_token *token, char *cmd);

#endif