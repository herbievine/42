/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:11:11 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 08:33:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"
#include "display.h"

/**
 * @brief The ft_lstnew() function allocates (with malloc(3)) and returns a new
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
		return (0);
	new->v = content;
	new->n = 0;
	return (new);
}

/**
 * @brief The ft_lstadd_front() function adds the element 'new' at the beginning
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
	new->n = head;
	*lst = new;
}

/**
 * @brief The ft_lstadd_back() function adds the element 'new' at the end of the
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
		last->n = new;
	}
	else
		*lst = new;
}

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
	while (lst && lst->n)
		lst = lst->n;
	return (lst);
}

/**
 * @brief The ft_lstclear() function deletes and frees the given node and every
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

/**
 * @brief The ft_lstprint() function prints the content of the using.
 *
 * @param lst
 */
// void	ft_lstprint(t_list *lst, char *msg)
// {
// 	while (lst && lst->v > -1)
// 	{
// 		ft_putstr_fd(msg, 1);
// 		ft_putstr_fd(": ", 1);
// 		ft_putnbr_base_fd(lst->v, "0123456789", 1);
// 		ft_putchar_fd('\n', 1);
// 		lst = lst->n;
// 	}
// }
