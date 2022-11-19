/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:53 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:24:19 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	g_fail_after = 3;
static int	g_total_allocs = 0;

/**
 * @brief The ft_test_malloc() function is a wrapper for malloc() that will
 * fail after a certain number of allocations.
 * 
 * @param s 
 * @return void* 
 */
void	*ft_test_malloc(size_t s)
{
	if (g_fail_after > 0 && g_total_allocs++ >= g_fail_after)
		return (0);
	return (malloc(s));
}
