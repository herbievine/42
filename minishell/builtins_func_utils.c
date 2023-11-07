/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:32:21 by codespace         #+#    #+#             */
/*   Updated: 2023/11/06 10:19:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "char.h"

bool	ft_check_is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && (str[i - 1] == '=' || !str[i - 1]
				|| !ft_isalnum(str[i - 1])))
			return (false);
		if (ft_isalnum(str[i]) || str[i] == '_'
			|| str[i] == '=')
			i++;
	}
	return (true);
}
