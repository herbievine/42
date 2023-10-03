/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:48 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/02 11:44:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

char	*ft_get_env(char *key);
void	ft_set_env(char *key, char *value);
void	ft_remove_env(char *key);
char	**ft_get_paths(void);

#endif