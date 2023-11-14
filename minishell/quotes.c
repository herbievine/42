/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:33 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/14 13:20:27 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"
#include "str.h"
#include "split.h"
#include "free.h"
#include "find_cmds.h"
#include "expand.h"
#include <stdio.h>

void	ft_suppress_quotes(t_subcommand *subcommands, t_token *tokens)
{
	char	*str;
	char	**splited_str;
	char	limitter;
	int		i;

	limitter = 0;
	while (tokens)
	{
		str = ft_strdup(tokens->value);
		i = -1;
		while (str[++i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				limitter = ft_type_token(str[i], limitter);
				splited_str = ft_split(str, limitter);
				free(str);
				if (splited_str[1] && splited_str[2])
					tokens->value = ft_fmt_path(splited_str[0],
										splited_str[1], splited_str[2]);
				else if (splited_str[1])
					tokens->value = ft_strjoin(splited_str[0], splited_str[1]);
				else
					tokens->value = ft_strdup(splited_str[0]);
				ft_free_array(splited_str, -1);
			}
		}
		tokens = tokens->next;
	}
}