/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:51 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 19:26:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "structs.h"

int ft_get_infile(t_pipex *pipex, char **argv);
int ft_get_outfile(t_pipex *pipex, char **argv, int argc);

#endif /* IO_H */