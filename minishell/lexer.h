/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:27:21 by herbie            #+#    #+#             */
/*   Updated: 2023/07/03 16:27:53 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"
# include <stdbool.h>

t_lexer		ft_lexer_new(const char *raw);
t_token		ft_lexer_next(t_lexer *lexer);

#endif /* LEXER_H */