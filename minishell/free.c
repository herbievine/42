/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:36 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 18:47:55 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "str.h"
#include "token.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

void	ft_free_all(t_subcommand *subcommand, t_token **token,
		bool do_you_want_to_free_the_env)
{
	if (do_you_want_to_free_the_env)
		ft_free_array(subcommand->envp, -1);
	ft_free_subcommands(subcommand);
	ft_clear_tokens(token);
}

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
			ft_free_array(subcommand->args, -1);
		tmp = subcommand->next;
		free(subcommand);
		subcommand = tmp;
	}
	return ;
}

// TODO check if used. if so, use ft_free_array instead
void	ft_free_cmds(char **split, size_t j)
{
	if (j != (size_t)(-1))
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
