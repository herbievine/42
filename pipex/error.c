/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 21:54:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"
#include "print.h"
#include "structs.h"
#include "io.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int	ft_err(char *err)
{
	ft_dprintf(2, "pipex: %s\n", err);
	exit(1);
	return (1);
}

void	ft_bash_not_found(char *cmd)
{
	char	*err_msg;
	char	*bash_msg;

	err_msg = ft_strjoin(cmd, ECFND);
	if (!err_msg)
		return ;
	bash_msg = ft_strjoin("bash: ", err_msg);
	free(err_msg);
	if (!bash_msg)
		return ;
	write(STDERR_FILENO, bash_msg, ft_strlen(bash_msg));
	write(STDERR_FILENO, "\n", 1);
	free(bash_msg);
}
