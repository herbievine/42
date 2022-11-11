/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:14:44 by hvine             #+#    #+#             */
/*   Updated: 2022/11/11 21:18:54 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_isdigit() function tests for a decimal digit character. Regardless
 * of locale, this includes the following characters only: '0' '1' '2' '3' '4'
 * '5' '6' '7' '8' '9'.
 * 
 * @param c 
 * @return int 
 */
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
