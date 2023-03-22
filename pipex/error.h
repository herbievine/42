/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:36 by herbie            #+#    #+#             */
/*   Updated: 2023/03/22 11:04:20 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

#define ERR_ARGS "Error: Invalid number of arguments"
#define ERR_FORK "Error: Fork failed"
#define ERR_PIPE "Error: Pipe failed"
#define ERR_EXEC "Error: Exec failed"

void error(char *err);

#endif /* ERROR_H */