/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:32:31 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 15:16:45 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "str.h"
#include "error.h"
//TODO: print error message
int	ft_define_exit_status(char *str_status, char *path)
{
	if (ft_strncmp(str_status, EACCES, ft_strlen(str_status)) == 0)
		return (126);
	if (ft_strncmp(str_status, ENOENT, ft_strlen(str_status)) == 0)
		return (127);
	if (ft_strncmp(str_status, ECMD, ft_strlen(str_status)) == 0)
		return (127);
	if (ft_strncmp(str_status, EUKN, ft_strlen(str_status)) == 0)
		return (127);
	if (ft_strncmp(str_status, EMALLOC, ft_strlen(str_status)) == 0)
		return (127);
	if (ft_strncmp(str_status, ESYN, ft_strlen(str_status)) == 0)
		return (2);
	if (ft_strncmp(str_status, ECNF, ft_strlen(str_status)) == 0)
		return (1);
	return (1);
}
