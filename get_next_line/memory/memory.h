/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:43:40 by herbie            #+#    #+#             */
/*   Updated: 2023/02/01 12:52:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

void *ft_record_malloc(size_t size);
void *ft_record_free(void *ptr);

#define malloc(x) ft_record_malloc(x)
