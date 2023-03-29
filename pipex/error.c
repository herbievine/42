/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/03/29 13:05:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

void error(char *err)
{
	if (errno)
		perror(err);
	else
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, "\n", 1);
	}
}

void bash_not_found(char *cmd)
{
	char *err_msg;
	char *bash_msg;

	err_msg = ft_strjoin(cmd, ": command not found\n");
	if (!err_msg)
		return (perror("malloc"), (void)0);
	bash_msg = ft_strjoin("bash: ", err_msg);
	if (!bash_msg)
		return (free(err_msg), perror("malloc"), (void)0);
	write(STDERR_FILENO, bash_msg, ft_strlen(bash_msg));
	free(err_msg);
	free(bash_msg);
}