/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:38:55 by herbie            #+#    #+#             */
/*   Updated: 2023/10/03 12:39:05 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char* substr(const char *src, int m, int n)
{
    // get the length of the destination string
    int len = n - m;
 
    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
 
    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
 
    // null-terminate the destination string
    *dest = '\0';
 
    // return the destination string
    return dest - len;
}


static char		**ft_init_split(char const *s, char c);
static void		ft_fill_split(char const *s, char **split, char c);
static void		ft_free(char **split, size_t j);

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = ft_init_split(s, c);
	if (!split)
		return (0);
	ft_fill_split(s, split, c);
	if (!split)
		return (0);
	return (split);
}

static char	**ft_init_split(char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 1;
	len = 0;
	if (!*s)
		return (calloc(1, sizeof(char *)));
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c && s[i - 1] != '\0')
			len++;
		i++;
	}
	if (s[i - 1] != c)
		len++;
	return ((char **)calloc(len + 1, sizeof(char *)));
}

static void	ft_fill_split(char const *s, char **split, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] != c)
			if (++i && ++len)
				continue ;
		if (len > 0)
		{
			split[j++] = substr(s, i - len, len);
			if (!split[j - 1])
			{
				ft_free(split, j);
				return ;
			}
		}
		if (s[i])
			i++;
	}
}

static void	ft_free(char **split, size_t j)
{
	if (j != -1)
	{
		while (j)
		{
			free(split[j]);
			j--;
		}
		free(split);
	}
	else
		while (*split)
			free(*split++);
}


char **envp;

/**
 * @brief The ft_get_env function returns the value of the environment variable
 * stored in the g_env variable. If the variable does not exist, NULL is
 * returned.
 *
 * @param key
 * @param envp
 * @return char*
 */
char	*ft_get_env(char *key)
{
	int		i;

	i = -1;
	while (envp[++i])
		if (strncmp(key, envp[i], strlen(key)) == 0
			&& envp[i][strlen(key)] == '=')
			return (strchr(envp[i], '=') + 1);
	return (NULL);
}

/**
 * @brief The ft_get_paths function returns an array of strings containing the
 * paths in the PATH environment variable. If the variable does not exist, NULL
 * is returned.
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_get_paths(void)
{
	char	*path;

	path = ft_get_env("PATH");
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

/**
 * @brief The ft_free_array function takes in an array and frees all memory.
 * If n if provided, it will only free the memory of the first n elements.
 *
 * @param array
 * @param n
 */
void	ft_free_array(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

char *ft_fmt_path(char *path, char *cmd);

/**
 * @brief The ft_find_path function finds the path of the command
 * in the PATH environment variable.
 *
 * @param cmd
 * @return char*
 */
char *ft_find_path(char *cmd)
{
	int i;
	char **paths;
	char *path;
	char *full_path;

	if (access(cmd, F_OK) == 0)
		return (substr(cmd, 0, strlen(cmd)));
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
char *ft_fmt_path(char *path, char *cmd)
{
	char *str;
	int len;
	int i;

	len = strlen(path) + strlen(cmd) + strlen("/");
	str = calloc(len + 1, sizeof(char));
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

int	main(int ac, char **av, char **ev)
{
	char	*path;
	char	*cmd;
	char	*full_path;

	envp = ev;

	if (ac != 2)
		return (1);
	cmd = av[1];
	full_path = ft_find_path(cmd);
	if (!full_path)
		return (1);
	printf("full_path: %s\n", full_path);
	free(full_path);
	return (0);
}
