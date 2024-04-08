/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:34:00 by herbie            #+#    #+#             */
/*   Updated: 2024/04/08 19:02:27 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "structs.h"

int		ft_on_keypress(int keysym, t_data *data);
int		ft_on_keyrelease(int keysym, t_data *data);
int		ft_on_close(t_data *data);
void	ft_move_player(t_data *data);

#endif /* HOOKS_H */
