/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:32:21 by codespace         #+#    #+#             */
/*   Updated: 2023/10/30 08:51:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "char.h"

bool	ft_check_is_valid_identifier(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (ft_isalnum(str[i][j]) || str[i][j] == '_' || str[i][j] == '=')
				j++;
			if (str[i][j] == '=' && str[i][j-1] == '=')
				return (false);
		}
		i++;
	}
	return (true);
}