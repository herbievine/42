/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/04/27 10:36:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "mlx/mlx.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	void	*mlx;
	void	*mlx_win;

	(void)argc;
	(void)argv;
	(void)envp;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	free(mlx);
	free(mlx_win);
	return (0);
}
