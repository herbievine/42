/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:08 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 14:42:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "structs.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 360

void	ft_init_window(t_data *data);
void	ft_render_bg(t_data *data);

#endif /* WINDOW_H */
