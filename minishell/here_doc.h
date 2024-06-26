/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:36:03 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/22 10:43:34 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_here_doc(t_subcommand *subcommand,
			t_token *token);

#endif
