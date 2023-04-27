/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/04/27 19:38:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"
#include <stdlib.h>

/**
 * @brief The ft_err function takes in a string and prints it to stderr.
 * It then exits the program with a return value of 1.
 * 
 * @param err 
 * @return int 
 */
int	ft_err(char *err)
{
	ft_dprintf(2, "pipex: %s\n", err);
	exit(1);
	return (1);
}
