/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:11:48 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/14 16:07:35 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structs.h"

char	**ft_env_init(char **envp);
char	*ft_env_get(char **env, char *key);
char	**ft_env_get_paths(char **env);
char	**ft_env_remove(char ***env, char *key);
char	**ft_env_set(char **env, char *key, char *value);

#endif