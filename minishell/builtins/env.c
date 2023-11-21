/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:59:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/21 14:59:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../display.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}