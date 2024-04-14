/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:05:30 by jcros             #+#    #+#             */
/*   Updated: 2024/04/09 14:13:11 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

# include "structs.h"

void	ft_calculate_fps(t_data *data);
void	ft_render_fps(t_data *data);
void	ft_init_fps(t_data *data);

#endif /* FPS_H */