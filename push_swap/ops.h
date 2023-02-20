/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:13 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 18:54:46 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "lists.h"

void	ft_rotate(t_list **list, char *op);
void	ft_push(t_list **src, t_list **dst, char *op);
void	ft_swap(t_list **list, char *op);
void	ft_reverse_rotate(t_list **list, char *op);

#endif /* OPS_H */