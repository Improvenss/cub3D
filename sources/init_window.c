/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:56:22 by gsever            #+#    #+#             */
/*   Updated: 2022/12/08 03:11:58 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Created cub3D window.
 * 
 * @param main 
 * @return int 
 */
int	init_cub3d_window(t_main *main)
{
	t_mlx	*mlx;

	mlx = main->mlx;
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_init()", "error."));
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (mlx->win == NULL)
		return (print_error(PROMPT, "mlx", "mlx_new_window()", "error."));
	return (0);
}
