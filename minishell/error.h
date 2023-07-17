/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:38:36 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 16:02:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define M "minishell: "
# define ECMD "invalid command"
# define EMALLOC "malloc error"
# define EUKN "unknown error"
# define ENOENT "no such file or directory"
# define ESYN "syntax error near unexpected token"

# include "structs.h"

// @deprecated
void	old_ft_error(char *msg);
void	ft_invalid_token(t_lexer lexer, t_token token);

#endif /* ERROR_H */
