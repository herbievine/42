/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:10:44 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 18:55:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_putptr_fd() function prints a pointer to the given file 
 * descriptor and returns the number of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int ft_putptr_fd(unsigned long long n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("0x0", fd));
	ft_putstr_fd("0x", fd);
	return (ft_putnbr_base_fd(n, "0123456789abcdef", fd) + 2);
}