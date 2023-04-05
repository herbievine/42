/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:36 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 12:15:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "structs.h"

# define ERR_ARGS "Error: Invalid number of arguments"
# define ERR_FORK "Error: Fork failed"
# define ERR_PIPE "Error: Pipe failed"
# define ERR_EXEC "Error: Exec failed"
# define ERR_OPEN "Error: Open failed"
# define ERR_DUP "Error: Dup failed"

void	error(char *err);
void	bash_not_found(char *cmd);
void	cleanup(t_pipex *pipex);

#endif /* ERROR_H */