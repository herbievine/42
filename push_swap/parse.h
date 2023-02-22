/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:50:03 by herbie            #+#    #+#             */
/*   Updated: 2023/02/22 10:44:18 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct args
{
	char	**str_array;
	int		*int_array;
	int		count;
	t_bool	is_malloced;
}				t_args;

t_args	*ft_parse_args(int argc, char **argv);
t_args	*ft_get_args_from_argv(int argc, char **argv);
t_args	*ft_get_args_from_str(char *str);
void	ft_check_if_args_are_numbers(t_args *arg, int count);
void	ft_check_duplicates(t_args *arg);

#endif /* PARSE_H */