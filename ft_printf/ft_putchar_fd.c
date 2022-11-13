/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:58:17 by herbie            #+#    #+#             */
/*   Updated: 2022/11/12 10:03:57 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief The ft_putchar_fd() function outputs the character 'c' to the given
 * file descriptor.
 * 
 * @param c 
 * @param fd 
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
