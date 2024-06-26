/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:40:49 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 15:40:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../structs.h"
#include "../env.h"

int	ft_unset(t_command *command, t_subcommand *subcommand)
{
	char	**args;

	args = subcommand->args;
	while (*args)
		ft_env_remove(command->env, *args++);
	return (0);
}
