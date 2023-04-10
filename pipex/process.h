/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:15:00 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 14:56:07 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structs.h"

t_bool	ft_spawn_child(t_pipex *pipex, char **envp, int idx);

#endif /* PROCESS_H */