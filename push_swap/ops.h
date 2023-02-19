/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:13 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 19:48:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "lists.h"

void	ft_rotate(t_list **list);
void	ft_push(t_list **src, t_list **dst);

#endif /* OPS_H */