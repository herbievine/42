/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:54 by herbie            #+#    #+#             */
/*   Updated: 2023/03/17 16:12:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # include <sys/types.h>
// # include <sys/uio.h>
// # include <unistd.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <fcntl.h>
// # include <string.h>
// # include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif /* BUFFER_SIZE */

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */