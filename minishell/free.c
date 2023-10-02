/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/20 15:29:16 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <unistd.h>
#include <stdio.h>
#include "str.h"

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
		if ((subcommand->in_fd != 0) && (subcommand->in_fd != -1) && (!subcommand->is_heredoc) && (subcommand->out_fd != subcommand->in_fd))
			close(subcommand->in_fd);
		if (subcommand->out_fd != 1)
		{
			close(subcommand->out_fd);
			if (ft_strncmp(subcommand->out_file_name, "tmp", 3) == 0)
				unlink("tmp");
			
		}
		if (subcommand->out_file_name != NULL)
			free(subcommand->out_file_name);	
		if (subcommand->path != NULL)
			free(subcommand->path);
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
