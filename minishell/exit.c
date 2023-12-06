/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:32:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 17:24:36 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "str.h"
#include "error.h"
#include "display.h"
#include <stdio.h>

#define STDERR_FILENO 2

#define EINVAL "Invalid argument"
#define EISDIR "Is a directory"
#define ENOENT "No such file or directory"
#define ENOEXEC "Exec format error"
#define ENOTDIR "Not a directory"
#define EPERM "Permission denied"

void	ft_print_error(char *status, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(status, STDERR_FILENO);
}

int	ft_define_exit_status(char *str_status, char *path, char *args)
{
	if (ft_strncmp(str_status, EINVAL, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, path), 1);
	else if (ft_strncmp(str_status, EISDIR, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, args), 126);
	else if (ft_strncmp(str_status, ENOENT, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, args), 127);
	else if (ft_strncmp(str_status, ENOEXEC, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, path), 126);
	else if (ft_strncmp(str_status, ENOTDIR, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, args), 126);
	else if (ft_strncmp(str_status, EPERM, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, path), 126);
	else if (ft_strncmp(str_status, EACCES, ft_strlen(str_status)) == 0)
		return (ft_print_error(str_status, path), 126);
	return (1);
}
