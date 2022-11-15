/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:10:44 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 08:44:19 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_putptr_fd(long long int n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("0x0", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		// n *= -1;
		ft_putstr_fd("0x", fd);
		return (ft_putnbr_base_fd(n, "0123456789abcdef", fd) + 3);
	}
	ft_putstr_fd("0x", fd);
	return (ft_putnbr_base_fd(n, "0123456789abcdef", fd) + 2);
}