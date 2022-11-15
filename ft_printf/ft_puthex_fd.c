/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:50:33 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 08:14:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_fd(long long int n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("0", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		return (ft_putnbr_base_fd(n, "0123456789abcdef", fd) + 1);
	}
	return (ft_putnbr_base_fd(n, "0123456789abcdef", fd));
}