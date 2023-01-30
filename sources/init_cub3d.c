/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:26:43 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 13:23:03 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Creating new screen image for rendered game (3D).
 * 
 * @param main 
 * @return int 
 */
int	init_cub3d_image(t_main *main)
{
	main->screen.ptr = mlx_new_image(main->mlx.ptr,
			(int)(WINDOW_W), (int)(WINDOW_H));
	if (main->screen.ptr == NULL)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.win);
		return (print_error(PROMPT, "mlx", "mlx_new_image()", "error."));
	}
	main->screen.addr = (int *)mlx_get_data_addr(main->screen.ptr,
			&main->screen.bpp,
			&main->screen.line_size, &main->screen.endian);
	if (main->screen.addr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_get_data_addr()", "error."));
	return (0);
}

/**
 * @brief Creating new window for cub3D :).
 * 
 * @param main 
 * @return int 
 */
int	init_cub3d_window(t_main *main)
{
	main->mlx.win = mlx_new_window(main->mlx.ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (main->mlx.win == NULL)
		return (print_error(PROMPT, "mlx", "mlx_new_window()", "error."));
	return (0);
}

/**
 * @brief Initializing MLX, window ang screen img.
 * 
 * @param main 
 * @return int 
 */
int	init_cub3d(t_main *main)
{
	main->mlx.ptr = mlx_init();
	if (main->mlx.ptr == NULL)
		return (print_error(PROMPT, "mlx", "mlx_init()", "error."));
	if (init_cub3d_window(main) == ERROR)
		return (ERROR);
	if (init_cub3d_image(main) == ERROR)
		return (ERROR);
	return (0);
}
