/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:12 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/02 12:02:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_cmds.h"
#include "split.h"
#include "str.h"
#include "str2.h"
#include "free.h"
#include "mem.h"
#include "parse.h"
#include "env.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool ft_find_cmd(t_subcommand *subcommand, char *cmd);
char	*ft_find_path(char *cmd);
char **ft_create_path(char **envp);
char	*ft_fmt_path(char *path, char *cmd);

bool	ft_set_cmd(t_token *token, t_subcommand *subcommand)
{
	char *path;
	int cmd_len;
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

bool ft_find_cmd(t_subcommand *subcommand, char *cmd)
{
	char *full_path;

	full_path = ft_find_path(cmd);
	if (!full_path)
		return (false);
	else
		return (subcommand->path = full_path, true);
}

char **ft_create_path(char **envp)
{
	char **paths;

	if (!envp)
		return (NULL);
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	paths = ft_split(*envp, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

// char *ft_find_path(char **envp, char *cmd)
// {
// 	char **paths;
// 	char *path;
// 	int i;

// 	paths = ft_create_path(envp);
// 	if (!paths)
// 		return (NULL);
// 	i = -1;
// 	while (paths[++i])
// 	{
// 		path = ft_strjoins(paths[i], "/", cmd);
// 		if (!path)
// 			return (ft_free_cmds(paths, -1), free(path), NULL);
// 		if (access(path, F_OK) == 0)
// 			return (ft_free_cmds(paths, -1), path);
// 		free(path);
// 	}
// 	return (ft_free_cmds(paths, -1), NULL);
// }

/**
 * @brief The ft_get_infile function takes in a pipex struct and the arguments
 * passed to the program. It then parses the arguments and returns the full
 * program path.
 *
 * @param cmd
 * @param envp
 * @return char*
 */
char	*ft_find_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*full_path;

	if (access(cmd, F_OK) == 0)
		return (ft_substr(cmd, 0, ft_strlen(cmd)));
	paths = ft_get_paths();
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_fmt_path(paths[i], cmd);
		if (!path)
			return (ft_free_array(paths, -1), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_array(paths, -1), path);
		free(path);
	}
	return (ft_free_array(paths, -1), NULL);
}

char	*ft_fmt_path(char *path, char *cmd)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(path) + ft_strlen(cmd) + ft_strlen("/");
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = 0;
	while (*path)
		str[i++] = *path++;
	str[i++] = '/';
	while (*cmd)
		str[i++] = *cmd++;
	str[i] = '\0';
	return (str);
}
