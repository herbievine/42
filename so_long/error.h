/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:21:02 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 11:24:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>

# define EMAP "Invalid map"
# define EIO "I/O error"
# define EUNKN "Unknown error"
# define ENOENT "No such file or directory"
# define EX11 "X11 error"
# define ETXTUR "Texture error"

void	ft_err(char *msg);

#endif /* ERROR_H */