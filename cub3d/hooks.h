/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:34:00 by herbie            #+#    #+#             */
/*   Updated: 2023/05/08 13:21:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "structs.h"

int	ft_on_keypress(int keysym, t_data *data);
int	ft_on_close(t_data *data);

#endif /* HOOKS_H */
