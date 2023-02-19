/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:14:50 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 11:16:26 by hvine            ###   ########.fr       */
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
		res += (num % radix) * ft_pow(10, i++);
		num /= radix;
	}
	return (res);
}
