/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/26 08:43:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <unistd.h>
#include <stdio.h>
#include "str.h"

void	ft_free_tab(char **tab);

void	ft_free_subcommands(t_subcommand *subcommand)
{
	t_subcommand	*tmp;

	if (!subcommand)
		return ;
	while (subcommand != NULL)
	{
		if (subcommand->is_heredoc)
			unlink(".here_doc_fd");
		if ((subcommand->in_fd > 1) && (subcommand->in_fd != -1))
			close(subcommand->in_fd);
		if (subcommand->out_fd > 1)
			close(subcommand->out_fd);
		if (subcommand->path != NULL)
			free(subcommand->path);
		if (subcommand->args != NULL)
			ft_free_tab(subcommand->args);
		tmp = subcommand->next;
		free(subcommand);
		subcommand = tmp;
	}
	return ;
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_cmds(char **split, size_t j)
{
	if (j != -1)
	{
		while (j)
		{
			free(split[j]);
			j--;
		}
		free(split);
	}
	else
		while (*split)
			free(*split++);
}

/**
 * @brief The ft_free_array function takes in an array and frees all memory.
 * If n if provided, it will only free the memory of the first n elements.
 *
 * @param array
 * @param n
 */
void	ft_free_array(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

void	ft_free_fd(int fd)
{
	if (fd > 1)
		close(fd);
}
