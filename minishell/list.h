/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:35:45 by herbie            #+#    #+#             */
/*   Updated: 2023/07/20 16:39:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "structs.h"

typedef struct s_anon_lst
{
	struct s_anon_lst	*next;
}	t_anon_lst;

void	*ft_lstfrom(t_anon_lst *lst, int index);

#endif /* LIST_H */