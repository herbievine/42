/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:15:23 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:19:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_bzero() function writes n zeroed bytes to the string s. If n is
 * zero, ft_bzero() does nothing.
 * 
 * @param s 
 * @param n 
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
