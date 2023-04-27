/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 12:25:30 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define INVALID_INPUT_FILE_NAME "error"

typedef enum e_bool
{
	false,
	true
}		t_bool;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	t_bool	is_invalid_input;
	t_bool	here_doc;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
}		t_pipex;

#endif /* STRUCTS_H */