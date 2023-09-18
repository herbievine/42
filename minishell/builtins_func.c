/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 19:57:39 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/23 11:04:05 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_func.h"
#include "env.h"
#include "display.h"
#include "str.h"
#include "str2.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int		ft_cd(t_subcommand *subcommand)
{
	char	*path;
	int		ret;

	ret = 0;
	if (!subcommand->args)
		path = ft_get_env("HOME", subcommand);
	else
		path = subcommand->args[0];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ret = 1;
	}
	ft_pwd(subcommand);
	return (ret);
}

int		ft_pwd(t_subcommand *subcommand)
{
	char	*path;

	path = getcwd(NULL, 100);
	ft_putstr_fd(path, subcommand->out_fd);
	ft_putstr_fd("\n", subcommand->out_fd);
	free(path);
	return (0);
}

int		ft_export(t_subcommand *subcommand)
{
	char **args;
	int i;

	args = subcommand->args;
	i = 0;
	while (args && args[i])
	{
		printf("args[%d] = %s\n", i, args[i]);
		if (ft_strchr(args[i], '='))
			ft_add_env(args[i], args[i+1], subcommand);
		printf("ok\n");
		i++;
	}
	return (0);
}

int		ft_unset(t_subcommand *subcommand)
{
	char **args;
	int i;

	args = subcommand->args;
	i = 0;
	while (args[i])
	{
		ft_remove_env(args[i], subcommand);
		i++;
	}
	return (0);
}

int		ft_env(t_subcommand *subcommand)
{
	int		i;

	i = 0;
	while (subcommand->envp[i])
	{
		ft_putstr_fd(subcommand->envp[i], subcommand->out_fd);
		ft_putstr_fd("\n", subcommand->out_fd);
		i++;
	}
	return (0);
}

int		ft_exit(t_subcommand *subcommand)
{
	int		i;

	i = 0;
	if (subcommand->args)
		i = ft_atoi(subcommand->args[0]);
	exit(i);
	return (0);
}

void	ft_print_in_dq(char option, char *args, int out_fd);
bool	ft_print_in_sq(char *args, int out_fd);
int		ft_print_the_path(char *arg, int out_fd, t_subcommand *subcommand, t_token *token);
int		ft_print_antislash(char *args, int i, int out_fd, t_token *token);
bool	ft_is_antislash(char c , t_token *token);
bool	ft_if_sq(char *args, t_token *token);

int		ft_echo(t_subcommand *subcommand, t_token *token)
{
	// char	option;
	// int		i;
	// int		j;
	// char	*path;
	
	// i = 0;
	// path = (char *)token->value;
	// path[ft_strlen(token->value)] = '\0';
	// printf("path = %s\n", path);
	// if (path[0] == '-' && (path[1] == 'n' || path[1] == 'e' || path[1] == 'E') && !path[2])
	// {
	// 	option = path[++i]; // args[i] = n, e, E donc augmente i pour passer au prochain args
	// 	token = token->next;
	// }
	// while (token)
	// {
	// 	j = 0;
	// 	path = (char *)token->value;
	// 	path[token->length] = '\0';
	// 	printf("path = %s\n", path);
	// 	while (path[j])
	// 	{
	// 		if (!ft_if_sq(path, token) && path[j] == '$')
	// 			j += ft_print_the_path(path, subcommand->out_fd, subcommand, token);
	// 		if (option == 'E' && ft_is_antislash(path[j] , token))
	// 			j += ft_putchar_fd(path[j], 1);
	// 		else 
	// 			j+= ft_print_antislash(path, j, 1, token);
	// 	}
	// 	if (token->next)
	// 		ft_putstr_fd(" ", subcommand->out_fd);
	// 	token = token->next;
	// }
	// printf ("ok");
	// if (!option || option != 'n')
	// 	ft_putchar_fd('\n', subcommand->out_fd);
	// return (0);




//////////////////////////////////////////////////////////////////////////////////////////////////////////	
	// char	**args;
	// char	option;
	// int		i;
	// int		j;
	
	// args = subcommand->args;
	// i = 0;
	// if (args[0][0] == '-' && (args[0][1] == 'n' || args[0][1] == 'e' || args[0][1] == 'E') && !args[0][2])
	// {
	// 	option = args[0][++i]; // args[i] = n, e, E donc augmente i pour passer au prochain args
	// 	token = token->next;
	// }
	// printf ("arggs[i] = %s\n\n\n\n", args[i]);
	// while (args[i])
	// {
	// 	j = 0;
	// 	while (args[i][j])
	// 	{
	// 		if (!ft_if_sq(args[i], token) && args[i][j] == '$')
	// 			j += ft_print_the_path(args[i], subcommand->out_fd, subcommand, token);
	// 		if (option == 'E' && ft_is_antislash(args[i][j] , token))
	// 			j += ft_putchar_fd(args[i][j], subcommand->out_fd);
	// 		else 
	// 			j+= ft_print_antislash(args[i], j, subcommand->out_fd, token);
	// 	}
	// 	if (args[i + 1])
	// 		ft_putstr_fd(" ", subcommand->out_fd);
	// 	printf("token->type = %d\n", token->type);
	// 	if (token->type == TOKEN_DQ || token->type == TOKEN_SQ)
	// 		token = token->next->next->next;
	// 	else
	// 		token = token->next;
	// 	printf("token->type = %d\n", token->type);
	// }
	// if (!option || option != 'n')
	// 	ft_putchar_fd('\n', subcommand->out_fd);
	// return (0);
	// (void)subcommand;
	// (void)token;	
	// printf("echo\n");
	return (0);
}

void	ft_print_in_dq(char option, char *args, int out_fd)
{
	int	i;

	i = 0;
	if (option == 'e')
	{
		while (args[i])
			ft_putchar_fd(args[i++], out_fd);
	}
	if (option == 'E')
	{
		while (args[i])
			ft_putchar_fd(args[i++], out_fd);
	}
	else
		ft_putstr_fd(args, out_fd);
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
	i = ft_strlen(path);
	free(path);
	return (i);
}

// if TOKEN_DQ always return false
bool	ft_if_sq(char *args, t_token *token)
{
	int i;

	i = 0;
	if (token->type == TOKEN_DQ)
		return (false);
	while (args[i])
	{
		if (args[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_print_in_sq(char *args, int out_fd)
{
	int i;

	i = 0;
	while (args[i])
	{
		ft_putchar_fd(args[i], out_fd);
		i++;
	}
	return (true);
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