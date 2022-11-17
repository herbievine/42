/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:50:33 by herbie            #+#    #+#             */
/*   Updated: 2022/11/17 17:35:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_puthex_fd() function outputs the hexadecimal representation of
 * the unsigned integer 'n' to the given file descriptor and returns the number
 * of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int	ft_puthex_fd(unsigned int n, int fd)
{
	return (ft_putnbr_base_fd((unsigned long)n, "0123456789abcdef", fd));
}
