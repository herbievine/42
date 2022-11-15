/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_up_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:15:37 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 08:18:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_up_fd(long long int n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("0", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		return (ft_putnbr_base_fd(n, "0123456789ABCDEF", fd) + 1);
	}
	return (ft_putnbr_base_fd(n, "0123456789ABCDEF", fd));
}