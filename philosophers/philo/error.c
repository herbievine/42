/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:02:05 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:44:51 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The ft_err function takes in a string and prints it to the standard
 * output, then exits the program with a return value of 1.
 *
 * @param err
 * @return int
 */
int	ft_err(char *err)
{
	printf("philo: %s\n", err);
	exit(1);
	return (1);
}
