/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_up_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:15:37 by herbie            #+#    #+#             */
/*   Updated: 2022/11/16 11:16:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_up_fd(unsigned int n, int fd)
{
	return (ft_putnbr_base_fd((unsigned long)n, "0123456789ABCDEF", fd));
}