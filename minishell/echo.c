/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:07:23 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/19 12:09:42 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "str.h"
#include "str2.h"
#include "env.h"
#include "display.h"



static int		ft_print_the_path(char *arg, int out_fd, t_subcommand *subcommand, t_token *token);
static int		ft_print_antislash(char *args, int i, int out_fd, t_token *token);
static bool		ft_is_antislash(char c , t_token *token);

int	ft_echo(t_token *token, t_subcommand *subcommand)
{
	char	option;
	int		i;
	int		j;

	i = 0;
	if (subcommand->args[0][0] == '-' && (subcommand->args[0][1] == 'n' || subcommand->args[0][1] == 'e' || subcommand->args[0][1] == 'E') && !subcommand->args[1])
		option = subcommand->args[i++][1];
	while (subcommand->args[i])
	{
		j = 0;
		while (subcommand->args[i][j])
		{
			if (token->type != TOKEN_SQ && subcommand->args[i][j] == '$')
				j += ft_print_the_path(subcommand->args[i], subcommand->out_fd, subcommand, token);
			if (option == 'E' && ft_is_antislash(subcommand->args[i][j] , token))
				j += ft_putchar_fd(subcommand->args[i][j], subcommand->out_fd);
			else 
				j += ft_print_antislash(subcommand->args[i], j, subcommand->out_fd, token);
		}
		if (subcommand->args[++i] != NULL)
			ft_putchar_fd(' ', subcommand->out_fd);
	}
	if (!option || option != 'n')
		ft_putchar_fd('\n', subcommand->out_fd);
	return (true);
}

int	ft_print_the_path(char *arg, int out_fd, t_subcommand *subcommand, t_token *token)
{
	int i;
	int j;
	char *path;
	char *env_path;

	i = 0;
	j = 1;
	while (arg[i] && arg[i] != '$')
		i++;
	while (arg[i + j] && arg[i + j] != ' ' && !ft_is_antislash(arg[i + j], token))
		j++;
	path = ft_substr(arg, i+1, j);
	env_path = ft_get_env(path, subcommand);
	ft_putstr_fd(env_path, out_fd);
	i = ft_strlen(arg);
	free(path);
	return (i);
}

bool	ft_is_antislash(char c, t_token *token)
{
	if (token->type == TOKEN_DQ && c == '\'')
		return (false);
	if (token->type == TOKEN_SQ && c == '\"')
		return (false);
	if (c == '\\' || c == '\"' || c == '\'' || c == '\n' || c == '\t' || c == '\v' || c == '\b' || c == '\r' || c == '\f' || c == '\a')
		return (true);
	return (false);
}

int	ft_print_antislash(char *args, int i, int out_fd, t_token *token)
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
		else if (!ft_is_antislash(args[i], token))
			ft_putchar_fd(args[i], out_fd);
		j++;
	return (j);
}