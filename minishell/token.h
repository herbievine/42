/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:05:20 by herbie            #+#    #+#             */
/*   Updated: 2023/07/15 13:15:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

# define PIPE_NOT_FOUND -1

int		ft_find_next_pipe(t_token *token);
bool	ft_append_token(t_token **tokens, t_token token);
bool	ft_clear_tokens(t_token **tokens);

#endif /* TOKEN_H */