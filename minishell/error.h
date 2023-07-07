/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:38:36 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 15:38:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ECMD "invalid command"
# define EMALLOC "malloc error"
# define EUKN "unknown error"

# include "structs.h"

void	ft_error(char *msg);
void	ft_invalid_token(char *command, t_lexer lexer, t_token token);

#endif /* ERROR_H */
