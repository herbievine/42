/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:08:14 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:17:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_lstlast() function returns the last node of the list.
 * 
 * @param lst 
 * @return t_list* 
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
