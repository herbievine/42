/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/21 16:59:36 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <unistd.h>

void	ft_free_tab(char **tab);

void	ft_free_subcommands(t_subcommand *subcommand)
{
	while (subcommand != NULL)
	{
		if (subcommand->is_heredoc)
		{
			close(subcommand->in_fd);
			unlink(".here_doc_fd");
		}
		if (subcommand->in_fd != 0 && subcommand->in_fd != -1 || subcommand->out_fd != 1)
			close(subcommand->in_fd);
		if (subcommand->out_fd != 1)
		{
			close(subcommand->out_fd);
			unlink("tmp");
		}
		if (subcommand->args != NULL)
			ft_free_tab(subcommand->args);
		subcommand = subcommand->next;
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
