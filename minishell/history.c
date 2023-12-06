/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 11:35:47 by codespace         #+#    #+#             */
/*   Updated: 2023/07/11 11:35:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	ft_history_new(void)
{
	using_history();
}

void	ft_history_add(char *buffer)
{
	add_history(buffer);
}

void	ft_history_clear(void)
{
	clear_history();
}
