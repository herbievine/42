/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:24:23 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 15:07:02 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "print.h"
#include "structs.h"
#include "free.h"
#include <stdlib.h>

/**
 * @brief The ft_err function prints the error message and exits the program 
 * with the status 1.
 * 
 * @param msg 
 */
void	ft_err(char *msg)
{
	ft_dprintf(2, "Error\n%s\n", msg);
	exit(1);
}
