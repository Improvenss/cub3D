/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:57:42 by gsever            #+#    #+#             */
/*   Updated: 2022/12/13 13:11:31 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Created cub3D window's mlx image.
 * 
 * @param main 
 * @return int 
 */
int	init_cub3d_image(t_main *main)
{
	t_mlx	*mlx;

	mlx = main->mlx;
	mlx->img.ptr = mlx_new_image(&mlx->ptr, WINDOW_W, WINDOW_H);
	if (mlx->img.ptr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_new_image()", "error."));
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.ptr,
		&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_get_data_addr()", "error."));
	return (0);
}

/**
 * @brief Created cub3D window's minimap image.
 * 
 * @param main 
 * @return int 
 */
int	init_minimap_image(t_main *main)
{
	t_mlx	*mlx;

	mlx = main->mlx;
	mlx->minimap.ptr = mlx_new_image(&mlx->ptr,
		(main->minimap.box_size * main->map.max_x),
		(main->minimap.box_size * main->map.max_y));
	if (mlx->img.ptr == NULL)
		return (print_error(PROMPT, "minimap", "mlx_new_image()", "error."));
	mlx->img.addr = (int *)mlx_get_data_addr(&mlx->img.ptr,
		&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (print_error(PROMPT, "minimap",
			"mlx_get_data_addr()", "error."));
	return (0);
}
