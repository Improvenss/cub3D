/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:01:25 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 23:28:01 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_window(t_main *main)
{
	t_mlx	*mlx;

	main->mlx = malloc(sizeof(t_mlx));
	if (main->mlx == NULL)
		return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	mlx = main->mlx;
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_init() error."));
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (mlx->win == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_new_window() error."));
	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_W, WINDOW_H);
	if (mlx->img.ptr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_new_image() error."));
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_get_data_addr() error."));
	mlx_hook(mlx->win, 2, 1L << 0, &actions_key_press, main);
	mlx_hook(mlx->win, 3, 1L << 1, actions_key_release, main);
	mlx_hook(mlx->win, 4, 0, &actions_mouse, main);
	mlx_hook(mlx->win, 17, 0, &mlx_free_kill_all, main);// close_window(); yapilacak
	return (0);
}

int	init_cub3d(t_main *main)
{
	main = malloc(sizeof(t_main));
	if (main == NULL)
		return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	main->key_val = 10000;
	// main->ply = malloc(sizeof(t_player));
	// if (main == NULL)
	// 	return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	// main->texture = malloc(sizeof(t_texture));
	// if (main == NULL)
	// 	return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	return (0);
}

int	init_all(t_main *main)
{
	if (init_cub3d(main) == ERROR)
		return (ERROR);
	if (init_window(main) == ERROR)
		return (ERROR);
	return (0);
}