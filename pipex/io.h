/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:51 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 15:28:51 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "structs.h"

t_bool	get_infile(t_pipex *pipex, char **argv);
t_bool	get_outfile(t_pipex *pipex, char **argv);

#endif /* IO_H */