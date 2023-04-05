/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:36 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 14:35:24 by codespace        ###   ########.fr       */
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

#endif /* ERROR_H */