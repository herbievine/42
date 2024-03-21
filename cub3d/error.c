/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:24:23 by herbie            #+#    #+#             */
/*   Updated: 2024/03/12 15:51:30 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "str.h"
#include <unistd.h>

/**
 * @brief The ft_err function prints the error message and exits the program 
 * with the status 1.
 * 
 * @param msg 
 */
void	ft_err(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	// exit(1);
}
