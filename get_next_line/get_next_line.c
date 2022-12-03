/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:30 by herbie            #+#    #+#             */
/*   Updated: 2022/11/30 15:52:24 by herbie           ###   ########.fr       */
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

char *ft_get_line(char *buffer, int fd)
{
	char *tmp;
	int bytes_out;

	bytes_out = 1;
	while (buffer && bytes_out != -1)
	{
		bytes_out = read(fd, tmp, BUFFER_SIZE);
		if (!tmp)
			return (0);
		if (ft_contains_newline(tmp))
		{
			char *cpy = tmp[ft_strnlen(tmp, '\n')];
			ft_strjoin(buffer, cpy);
			return (tmp + ft_strnlen(tmp, '\n'));
		}
		else
			ft_strjoin(buffer, tmp);
	}
}

char *get_next_line(int fd)
{
	static char *buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc((BUFFER_SIZE - 1) * sizeof(char));
	if (!buffer)
		return (0);
	ft_get_line(buffer, fd);
}

int main()
{
	char *t = "this a  test which includes\n a bunch of data and a lot \nof newlines too lol\n\n\n";
}
