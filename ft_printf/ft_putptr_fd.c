/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:10:44 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_putptr_fd funtion prints a pointer to the given file 
 * descriptor and returns the number of bytes written.
 * 
 * @param ptr 
 * @param fd 
 * @return int 
 */
int	ft_putptr_fd(void *ptr, int fd)
{
	if (!ptr && __MACH__)
		return (ft_putstr_fd("0x0", fd));
	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	ft_putstr_fd("0x", fd);
	return (ft_putnbr_base_fd((unsigned long)ptr, "0123456789abcdef", fd) + 2);
}
