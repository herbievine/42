/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:15:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/01 12:44:02 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void *ft_record_malloc(size_t size)
{
	void *(*std_malloc)(size_t) = (void *(*))dlsym(RTLD_NEXT, "malloc");
	void *ptr = std_malloc(size);

	printf("creating new malloc <%p>\n", ptr);

	return (ptr);
}

void *ft_record_free(void *ptr)
{
	void *(*std_free)(void *) = (void *(*))dlsym(RTLD_NEXT, "free");

	printf("freeing malloc <%p>\n", ptr);

	std_free(ptr);
}