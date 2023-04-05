/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:16:50 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 12:30:53 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

t_bool	ft_parse_args(t_pipex *pipex, int argc, char **argv);
t_bool	ft_parse_cmd_path(t_pipex *pipex, int argc, char **argv, char **envp);
t_bool	ft_parse_cmd_args(t_pipex *pipex, int argc, char **argv);
char	*ft_find_path(char *cmd, char **envp);

#endif /* PARSE_H */