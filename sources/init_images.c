/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 02:57:42 by gsever            #+#    #+#             */
/*   Updated: 2022/12/10 23:22:34 by gsever           ###   ########.fr       */
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
	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_W, WINDOW_H);
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
	// ft_putnbr_fd(main->minimap.box_size, 1); ft_putchar_fd('\n', 1);
	// ft_putnbr_fd(main->map.max_x, 1); ft_putchar_fd('\n', 1);
	// ft_putnbr_fd(main->map.max_y, 1); ft_putchar_fd('\n', 1);
	// ft_putnbr_fd(main->minimap.box_size * main->map.max_x, 1); ft_putchar_fd('\n', 1);
	ft_putstr_fd(B_CYAN"minimap img start\n"END, 1);

	main->minimap.img.ptr = mlx_new_image(&main->mlx->ptr,
		(main->minimap.box_size * main->map.max_x),
		(main->minimap.box_size * main->map.max_y));

	ft_putstr_fd(B_CYAN"minimap img ok\n"END, 1);

	if (main->minimap.img.ptr == NULL)
		return (print_error(PROMPT, "minimap", "mlx_new_image()", "error."));

	main->minimap.img.addr = (int *)mlx_get_data_addr(&main->minimap.img.ptr,
		&main->minimap.img.bits_per_pixel,
		&main->minimap.img.line_length, &main->minimap.img.endian);

	if (main->minimap.img.addr == NULL)
		return (print_error(PROMPT, "minimap",
			"mlx_get_data_addr()", "error."));
	return (0);
}
