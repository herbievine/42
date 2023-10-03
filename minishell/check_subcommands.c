/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subcommands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:51:56 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/03 12:56:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_subcommands.h"
#include "error.h"
#include "parse.h"
#include <stdio.h>

bool	ft_check_subcommands(t_subcommand *subcommand, t_token *token)
{
	if (!subcommand->path && !ft_is_io_symbol(token))
		return (printf("minishell: %.*s: command not found\n", token->length, token->value), false);
	if (subcommand->builtin)
		return(false);
	return (true);
}