/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:26 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/06 19:59:40 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CMDS_H
# define FIND_CMDS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_path(t_subcommand *subcommand, t_token *token);
char	*ft_fmt_path(char *s1, char *s2, char *s3);

#endif
