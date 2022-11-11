/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:58:17 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:13:30 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
