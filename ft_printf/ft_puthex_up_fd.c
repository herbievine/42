/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_up_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:15:37 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_puthex_up_fd funtion outputs the hexadecimal representation
 * of the unsigned integer 'n' to the given file descriptor and returns the
 * number of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int	ft_puthex_up_fd(unsigned int n, int fd)
{
	return (ft_putnbr_base_fd((unsigned long)n, "0123456789ABCDEF", fd));
}
