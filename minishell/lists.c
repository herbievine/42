/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:11:11 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include "display.h"
#include <stdlib.h>

/**
 * @brief The ft_lstnew funtion allocates (with malloc(3)) and returns a new
 * element. The variable 'content' is initialized with the value of the
 * parameter 'content'. The variable 'next' is initialized to NULL.
 *
 * @param content
 * @return t_list*
 */
t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}

/**
 * @brief The ft_lstadd_front funtion adds the element 'new' at the beginning
 * of the list.
 *
 * @param lst
 * @param new
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	if (!lst || !new)
		return ;
	new->next = head;
	*lst = new;
}

/**
 * @brief The ft_lstadd_back funtion adds the element 'new' at the end of the
 * list.
 *
 * @param lst
 * @param new
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

/**
 * @brief The ft_lstlast funtion returns the last node of the list.
 *
 * @param lst
 * @return t_list*
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->n)
		lst = lst->n;
	return (lst);
}

/**
 * @brief The ft_lstclear funtion deletes and frees the given node and every
 * successor of that node, using the function 'del' and free(3).
 *
 * @param lst
 * @param del
 */
void	ft_lstclear(t_list **lst)
{
	t_list	*head;
	t_list	*tmp;

	if (!lst)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head->n;
		free(head);
		head = tmp;
	}
	*lst = NULL;
}
