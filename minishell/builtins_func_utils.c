/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:32:21 by codespace         #+#    #+#             */
/*   Updated: 2023/11/16 12:18:00 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "char.h"
#include <stdio.h>

bool	ft_check_is_valid_identifier(char *str, int type)
{
	int	i;
	int	have_alpha;

	i = 0;
	if (type == TOKEN_DQ || type == TOKEN_SQ)
		return (true);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			have_alpha = true;
		if (str[i] == '=' && (str[i - 1] == '=' || !str[i - 1]
				|| !ft_isalnum(str[i - 1])))
			return (false);
		else if (str[i] && str[i] != '='
			&& !ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	if (!have_alpha || i == 0 || str[i - 1] == '=')
		return (false);
	return (true);
}
