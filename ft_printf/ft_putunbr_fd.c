/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:07:39 by herbie            #+#    #+#             */
/*   Updated: 2022/11/17 17:35:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_putunbr_fd() function outputs the unsigned integer 'n' to the
 * given file descriptor and returns the number of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n == 0)
		return (ft_putstr_fd("0", fd));
	return (ft_putnbr_base_fd(n, "0123456789", fd));
}
