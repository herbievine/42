/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 15:34:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_bool
{
	false,
	true
} t_bool;

typedef struct s_fd_pair
{
	long fd[2];
} t_fd_pair;

typedef struct s_pipex
{
	int in_fd;
	int out_fd;
	t_bool here_doc;
} t_pipex;

#endif /* STRUCTS_H */