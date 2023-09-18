/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subcommands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:51:56 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/19 18:06:12 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_subcommands.h"
#include "error.h"
#include "parse.h"
#include <stdio.h>

bool	ft_check_subcommands(t_subcommand *subcommand, t_token *token)
{
	if (!subcommand->path && !ft_valid_token(token))
		return (printf("minishell: %.*s: command not found\n", token->length, token->value), false);
	return (true);
}