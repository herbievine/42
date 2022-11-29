/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:30 by herbie            #+#    #+#             */
/*   Updated: 2022/11/29 10:06:44 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_contains_newline(char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}

char *ft_get_line(char *prev_cursor, int fd)
{
	char *tmp;

	while (*prev_cursor)
	{
		tmp = read(fd, prev_cursor, BUFFER_SIZE);
		if (!tmp)
			return (0);
		if (ft_contains_newline(tmp))
		{
		}
	}
}

char *get_next_line(int fd)
{
	static char *cursor;
	char *buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	cursor = malloc((BUFFER_SIZE - 1) * sizeof(char));
	buffer = malloc((BUFFER_SIZE - 1) * sizeof(char));
	if (!cursor || !buffer)
		return (0);
	ft_get_line(cursor, fd);
	return (buffer);
}

int main()
{
	char *t = "this a  test which includes\n a bunch of data and a lot \nof newlines too lol\n\n\n";
}
