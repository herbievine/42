/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:03:09 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/24 22:22:16 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "str.h"
#include "env.h"
#include "char.h"
#include "lexer_utils.h"
#include <unistd.h>
#include <stdio.h>

int	ft_is_exit_status(t_subcommand *subcommand,
	t_token *token, char **str, int i)
{
	char	*expanded;
	char	*tmp;
	char	*tmp2;
	int		len;

	expanded = ft_itoa(g_signal);
	if (!expanded)
		return (-1);
	tmp = ft_substr((*str), 0, i);
	if (!tmp)
		return (free(expanded), -1);
	tmp2 = ft_strjoin(tmp, expanded);
	(free(tmp), free(expanded));
	if (!tmp2)
		return (-1);
	len = ft_strlen(tmp2);
	tmp = ft_substr((*str), i + 2, ft_strlen((*str)) - i - 2);
	if (!tmp)
		return (free(tmp2), -1);
	free((*str));
	(*str) = ft_strjoin(tmp2, tmp);
	(free(tmp2), free(tmp));
	if (!(*str))
		return (-1);
	return (len);
}

char	*ft_fill_following_str(char *str, int i)
{
	char	*full_string;
	char	*tmp;

	while (str[i] && str[i] != '$'
		&& str[i] != '\'' && str[i] != '"' 
		&& !ft_isspace(str[i]))
		i++;
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		return (NULL);
	full_string = ft_strjoin(tmp, "");
	free(tmp);
	if (!full_string)
		return (NULL);
	return (full_string);
}

int	ft_expand_string(t_subcommand *subcommand, char **str, int i)
{
	char	*expanded;
	char	*tmp;
	char	*tmp2;

	if ((*str)[i] == '$' && (*str)[i + 1] == '?')
		return (ft_is_exit_status(subcommand, NULL, str, i));
	tmp = ft_substr((*str), 0, i);
	if (!tmp)
		return (-1);
	expanded = ft_expand_dollar(subcommand, (*str) + i);
	if (!expanded)
		return (free(tmp), -1);
	tmp2 = ft_strjoin(tmp, expanded);
	free(tmp);
	if (!tmp2)
		return (-1);
	tmp = ft_fill_following_str(*str, i + 1);
	if (!tmp)
		return (free(tmp2), -1);
	free((*str));
	(*str) = ft_strjoin(tmp2, tmp);
	(free(tmp2), free(tmp));
	if (!(*str))
		return (-1);
	return (ft_strlen(expanded) + i);
}

bool	ft_check_validity(char *str, int i, char limiter)
{
	if (str[i]
		&& ft_is_valid_symbol(str[i + 1])
		&& !ft_isspace(str[i + 1])
		&& str[i] == '$' && limiter != '\'' )
		return (true);
	return (false);
}