/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subcommands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:51:56 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/10 17:22:26 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_subcommands.h"
#include "error.h"
#include "parse.h"
#include <stdio.h>

bool	ft_check_subcommands(t_subcommand *subcommand, t_token *token)
{
	if (subcommand->builtin)
		return (false);
	return (true);
}
