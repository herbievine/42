/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:07:23 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/11 17:44:08 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "str.h"
#include "env.h"
#include "display.h"
#include "expand.h"
#include <stdio.h>

static int	ft_print_the_path(char *arg, int i,
				t_subcommand *subcommand, int type);
static int	ft_print_antislash(char *args, int i, int out_fd, int type);
static bool	ft_what_to_print(t_subcommand *subcommand,
				t_token *token, int i, int type);

int	ft_echo(t_token *token, t_subcommand *subcommand)
{
	int		option;
	int		i;
	int		type;

	i = 0;
	type = 2;
	option = 0;
	if (subcommand->args[1] && ft_strncmp(subcommand->args[1], "-n", 2) == 0
		&& ft_strlen(subcommand->args[1]) == 2)
		option = 1;
	while (subcommand->args[++i] && token)
	{
		type = ft_type_token(token, type);
		// printf ("type = %d\n", type);
		// printf("subcommand->args[%d] = %s\n", i, subcommand->args[i]);
		// printf("token->value = %s\n", token->value);
		// printf("token->type = %d\n", token->type);
		ft_what_to_print(subcommand, token, i, type);
		token = token->next;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return (true);
}

bool	ft_what_to_print(t_subcommand *subcommand,
				t_token *token, int i, int type)
{
	int	j;

	j = 0;
	while (subcommand->args[i][j])
	{
		if (type != TOKEN_SQ && subcommand->args[i][j] == '$')
			j += ft_print_the_path(subcommand->args[i],
					j, subcommand, type);
		else
			j += ft_print_antislash(subcommand->args[i],
					j, subcommand->out_fd, type);
	}
	if (token && token->next && token->type != TOKEN_SQ && token->type != TOKEN_DQ 
		&& token->next->type != TOKEN_SQ && token->next->type != TOKEN_DQ
		&& j > 0 && subcommand->args[i] && subcommand->args[i + 1])
		ft_putchar_fd(' ', subcommand->out_fd);
	return (true);
}

static int	ft_print_the_path(char *arg, int i,
				t_subcommand *subcommand, int type)
{
	int		j;
	char	*path;
	char	*env_path;

	j = 1;
	env_path = NULL;
	while (arg[i] && arg[i] != '$')
		i++;
	while (arg[i] && arg[i + j] && arg[i + j] != ' '
		&& !ft_is_antislash(arg[i + j], type, 0))
		j++;
	if (arg[i + 1] == '?')
		j = 2;
	path = ft_substr(arg, i, j);
	env_path = ft_expand_dollar(subcommand, path);
	free(path);
	if (env_path)
		ft_putstr_fd(env_path, subcommand->out_fd);
	return (j);
}

static int	ft_print_antislash(char *args, int i, int out_fd, int type)
{
	int	j;

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
