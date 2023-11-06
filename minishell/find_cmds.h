/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:26 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/03 11:41:13 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CMDS_H
# define FIND_CMDS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_path(t_subcommand *subcommand, t_token *token);
char	*ft_fmt_path(char *s1, char *s2, char *s3);

#endif