// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   memory.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/12/17 16:15:05 by herbie            #+#    #+#             */
// /*   Updated: 2022/12/17 16:26:11 by herbie           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <dlfcn.h>
// #include <stdlib.h>

// typedef struct ptr_list
// {
// 	unsigned int address;
// 	size_t size;
// 	ptr_list *next;
// } ptr_list;

// static unsigned int *ptr_list;

// void add_pointer(void *ptr)
// {
// 	unsigned int p = (unsigned int)ptr;
// }

// void *ft_malloc(size_t size)
// {
// 	void *(*std_malloc)(sizet_t) = (void *(*)size_t)dlsym(RTLD_NEXT, "malloc");
// 	void *ptr = std_malloc(size);
// 	return (ptr);
// }

// void *ft_free(void *ptr)
// {
// 	void *(*std_free)(void *) = (void *(*)size_t)dlsym(RTLD_NEXT, "free");
// 	std_free(ptr);
// }