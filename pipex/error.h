/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:36 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 21:55:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "structs.h"

# define EARGS "error: invalid arguments"
# define EUNKN "error: unknown error"
# define ECFND "error: command not found"
# define ENOENT "error: no such file or directory"

int		ft_err(char *err);
void	ft_bash_not_found(char *cmd);

#endif /* ERROR_H */
