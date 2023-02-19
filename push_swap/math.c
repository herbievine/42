/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:15:24 by hvine             #+#    #+#             */
/*   Updated: 2023/02/19 21:24:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <math.h>

/**
 * @brief The ft_pow() function returns the value of nb raised to the power of
 * power.
 *
 * @param nb
 * @param power
 * @return int
 */
int	ft_pow(int nb, int power)
{
	int	res;

	if (nb == 0)
		return (0);
	if (nb == 1 || power == 0)
		return (1);
	res = nb;
	while (--power)
		res *= nb;
	return (res);
}

int	ft_binary_length(int n)
{
	if (n > 64 && n % 2 != 0)
		return (log2(n) + 2);
	else
		return (log2(n) + 1);
}
