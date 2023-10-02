/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:12 by juliencros        #+#    #+#             */
/*   Updated: 2023/09/20 15:23:51 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_cmds.h"
#include "split.h"
#include "str.h"
#include "free.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool		ft_find_cmd(t_subcommand *subcommand, char *cmd);
char		*ft_find_path(char **envp, char *cmd);
char		**ft_create_path(char **envp);
char		*ft_strjoins(char *s1, char *s2, char *s3);

bool	ft_set_cmd(t_token *token, t_subcommand *subcommand)
{
	char	*path;
	int		cmd_len;
	if (ft_valid_token(token))
		token = token->next->next;
	if (!token || token->type == TOKEN_PIPE || subcommand->builtin == 1)
		return (true);
	cmd_len = token->length;
	path = (char *)token->value;
	path[cmd_len] = '\0';
	if (ft_strncmp(path, "/bin/", 5) == 0)
	{
		if (access(path, F_OK) != -1)
			return (subcommand->path = path, true);
	}
	ft_find_cmd(subcommand, path);
	return (true);
}

bool	ft_find_cmd(t_subcommand *subcommand, char *cmd)
{
	char	*full_path;

	full_path = ft_find_path(global_env, cmd);
	if (!full_path)
		return (false);
	else
		return (subcommand->path = full_path, true);
}

char	**ft_create_path(char **envp)
{
	char	**paths;

	if (!envp)
		return (NULL);
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split(*envp, ':');
	if (!paths)
		return (NULL); 
	return (paths);
}

char	*ft_find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_create_path(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i]) 
	{
		path = ft_strjoins(paths[i], "/", cmd);
		if (!path)
			return (ft_free_cmds(paths, -1), free(path), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_cmds(paths, -1), path);
		free(path);
	}
	return (ft_free_cmds(paths, -1), NULL);
}

char	*ft_strjoins(char *s1, char *s2, char *s3)
{
	char	*final_str;
	int		i;

	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	final_str = malloc(sizeof(char) * i + 1);
	if (!final_str)
		return (NULL);
	i = 0;
	while (*s1)
		final_str[i++] = *s1++;
	while (*s2)
		final_str[i++] = *s2++;
	while (*s3)
		final_str[i++] = *s3++;
	final_str[i] = '\0';
	return (final_str);
}
