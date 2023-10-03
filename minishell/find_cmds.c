/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:12 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/03 12:56:38 by herbie           ###   ########.fr       */
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

static char	*ft_find_path(char *cmd);
static char	*ft_fmt_path(char *path, char *cmd);

/**
 * @brief The ft_set_path function sets the path of the command.
 * If the command is a builtin, the path is set to NULL. If the command
 * is not a builtin, the path is set to the full path of the command
 * found in the PATH environment variable.
 * 
 * @param subcommand 
 * @param token 
 * @return bool 
 */
bool	ft_set_path(t_subcommand *subcommand, t_token *token)
{
	char	*cmd;
	char	*path;
	int		cmd_len;

	if (ft_is_io_symbol(token))
		token = token->next->next;
	if (!token || token->type == TOKEN_PIPE || subcommand->builtin == 1)
		return (true);
	cmd = ft_substr(token->value, 0, token->length);
	if (ft_strncmp(cmd, "/bin/", 5) == 0)
	{
		if (access(cmd, F_OK) != -1)
			return (subcommand->path = cmd, true);
	}
	path = ft_find_path(cmd);
	if (!path)
		return (false);
	return (subcommand->path = path, true);
}

/**
 * @brief The ft_find_path function finds the path of the command
 * in the PATH environment variable.
 *
 * @param cmd
 * @return char*
 */
static char	*ft_find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

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

/**
 * @brief The ft_fmt_path function returns the full path of the command.
 *
 * @param path
 * @param cmd
 * @return char*
 */
static char	*ft_fmt_path(char *path, char *cmd)
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
