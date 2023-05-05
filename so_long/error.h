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

# include "structs.h"

# define EMAP "Invalid map"
# define EIO "Input/output error"
# define EUNKN "Unknown error"
# define ENOENT "No such file or directory"

void	ft_err(char *msg, t_map *map);

#endif /* ERROR_H */