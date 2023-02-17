/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:14:50 by herbie            #+#    #+#             */
/*   Updated: 2023/02/17 21:32:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"
#include "math.h"

int ft_to_radix(int num, int radix)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (num)
	{
		res += (num % radix) * pow(10, i++);
		num /= radix;
	}
	return res;
}