/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:20:01 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/13 15:33:44 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

bool	ft_is_antislash(char c, char type, int care_of_quote)
{
	if (care_of_quote == 1)
	{
		if (type == '"' && c == '\'')
			return (false);
		if (type == '\'' && c == '"')
			return (false);
	}
	if (c == '\\' || c == '\'' || c == '"' || c == '\n'
		|| c == '\t' || c == '\v' || c == '\b'
		|| c == '\r' || c == '\f' || c == '\a')
		return (true);
	return (false);
}
