/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:05:20 by herbie            #+#    #+#             */
/*   Updated: 2023/12/03 08:01:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

# define PIPE_NOT_FOUND -1

int		ft_find_next_pipe(t_token *token);
bool	ft_append_token(t_token **tokens, t_token token);
bool	ft_clean_tokens(t_token **token);
bool	ft_free_tokens(t_token **tokens);

#endif /* TOKEN_H */
