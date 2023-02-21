/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:50:03 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 22:54:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct args
{
	char	**argv;
	int		*args;
	int		argc;
}				t_args;

t_args	*ft_parse_args(int argc, char **argv);
t_args	*ft_get_args_from_argv(int argc, char **argv);
t_args	*ft_get_args_from_str(char *str);
void	ft_check_if_args_are_numbers(int argc, char **argv);

#endif /* PARSE_H */