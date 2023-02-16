/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:01:28 by herbie            #+#    #+#             */
/*   Updated: 2023/02/16 09:44:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_putendl_fd() function outputs the string 's' to the given file
 * descriptor, followed by a newline.
 *
 * @param s
 * @param fd
 */
int ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (0);
	return (ft_putstr_fd(s, fd) + ft_putchar_fd('\n', fd));
}
