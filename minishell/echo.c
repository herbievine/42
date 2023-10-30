/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:07:23 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/26 12:23:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "str.h"
#include "str2.h"
#include "env.h"
#include "display.h"
#include "expand.h"
#include <stdio.h>


static int		ft_print_the_path(char *arg, int out_fd, t_subcommand *subcommand, int type);
static int		ft_print_antislash(char *args, int i, int out_fd, int type);
static bool		ft_is_antislash(char c , int type, int care_of_quote);

int	ft_echo(t_token *token, t_subcommand *subcommand)
{
	char option;
	int i;
	int j;
	int type;

	i = 1;
	j = 0;
	type = 2;
	if ((subcommand->args[0][0] == '-') && ((subcommand->args[0][1] == 'n' || subcommand->args[0][1] == 'e' || subcommand->args[0][1] == 'E'))) //  && !subcommand->args[1]) je sais pas pourquoi
		option = subcommand->args[i++][1];
	while (subcommand->args[i] && token)
	{
		j = 0;
		while (subcommand->args[i][j])
		{
			if(token->type != 2)
				type = token->type;
			if (type != TOKEN_SQ && subcommand->args[i][j] == '$')
					j += ft_print_the_path(subcommand->args[i], subcommand->out_fd, subcommand, type);
			else if (option == 'E' && ft_is_antislash(subcommand->args[i][j] , type, 1) && subcommand->args[i][j] != '\'' && subcommand->args[i][j] != '\"')
				j += ft_putchar_fd(subcommand->args[i][j], subcommand->out_fd);
			else
				j += ft_print_antislash(subcommand->args[i], j, subcommand->out_fd, type);
		}
		if (type != TOKEN_SQ && type != TOKEN_DQ)
			ft_putchar_fd(' ', subcommand->out_fd);
		i++;
		token = token->next;
	}
	if (!option || option != 'n')
		ft_putchar_fd('\n', 1);
	return (true);
}

int	ft_print_the_path(char *arg, int out_fd, t_subcommand *subcommand, int type)
{
	int i;
	int j;
	char *path;
	char *env_path;

	i = 0;
	j = 1;
	while (arg[i] && arg[i] != '$')
		i++;
	while (arg[i + j] && arg[i + j] != ' ' && !ft_is_antislash(arg[i + j], type, 0))
		j++;
	path = ft_substr(arg, i, j);
	env_path = ft_expand_dollar(subcommand, path);
	if (env_path != NULL)
		ft_putstr_fd(env_path, out_fd);
	free(path);
	return (j);
}

bool	ft_is_antislash(char c, int type, int care_of_quote)
{
	if (care_of_quote == 1)
	{
		if (type == TOKEN_DQ && c == '\'')
			return (false);
		if (type == TOKEN_SQ && c == '\"')
			return (false);
	}
	if (c == '\\' || c == '\'' || c == '\"' ||   c == '\n' || c == '\t' || c == '\v' || c == '\b' || c == '\r' || c == '\f' || c == '\a')
		return (true);
	return (false);
}

int	ft_print_antislash(char *args, int i, int out_fd, int type)
{
	int j;

	j = 0;
		if (args[i] == '\\')
		{
			if (args[i + 1] == 'n')
				ft_putchar_fd('\n', out_fd);
			else if (args[i + 1] == 't')
				ft_putchar_fd('\t', out_fd);
			else if (args[i + 1] == 'v')
				ft_putchar_fd('\v', out_fd);
			else if (args[i + 1] == 'b')
				ft_putchar_fd('\b', out_fd);
			else if (args[i + 1] == 'r')
				ft_putchar_fd('\r', out_fd);
			else if (args[i + 1] == 'f')
				ft_putchar_fd('\f', out_fd);
			else if (args[i + 1] == 'a')
				ft_putchar_fd('\a', out_fd);
			j++;
		}
		else if (!ft_is_antislash(args[i], type, 1))
			ft_putchar_fd(args[i], out_fd);
		j++;
	return (j);
}