/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:21:02 by herbie            #+#    #+#             */
/*   Updated: 2024/03/05 13:43:01 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>

# define EMAP "Invalid map"
# define EARG "Invalid arguments"
# define EIO "I/O error"
# define EUNKN "Unknown error"
# define ENOENT "No such file or directory"
# define EX11 "X11 error"
# define ETXTUR "Texture error"

void	ft_err(char *msg);

#endif /* ERROR_H */
