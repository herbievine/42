/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:10:58 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 19:44:57 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>

typedef struct s_list
{
	int content;
	struct s_list *next;
} t_list;

t_list *ft_lstnew(int content);
void ft_lstadd_front(t_list **lst, t_list *new);
void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
void ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstprint(t_list *lst, char *msg);

#endif /* LISTS_H */