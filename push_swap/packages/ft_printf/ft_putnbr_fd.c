/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:06:32 by herbie            #+#    #+#             */
/*   Updated: 2022/11/17 17:35:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_putnbr_fd() function outputs the integer 'n' to the given
 * file descriptor and returns the number of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
		return (ft_putnbr_base_fd(num, "0123456789", fd) + 1);
	}
	return (ft_putnbr_base_fd(num, "0123456789", fd));
}
