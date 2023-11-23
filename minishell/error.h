/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:38:36 by herbie            #+#    #+#             */
/*   Updated: 2023/11/23 11:01:26 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define M "minishell: "
# define ECMD "invalid command"
# define EMALLOC "malloc error"
# define EUKN "unknown error"
# define ENOENT "No such file or directory"
# define ESYN "syntax error near unexpected token"
# define ECNF "command not found"
# define EACCES "permission denied"

# include "structs.h"

// @deprecated
void	old_ft_error(char *msg);
void	ft_invalid_token(t_lexer lexer, t_token token);
void	ft_error(char *error, char *path);
void	ft_perror(char *message);

#endif /* ERROR_H */
