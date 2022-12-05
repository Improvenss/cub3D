/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:45:58 by gsever            #+#    #+#             */
/*   Updated: 2022/12/05 14:11:23 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_mlx_draw(t_main *main)
{
	printf("player before x[%f] y[%f]\n", main->ply.pos_x, main->ply.pos_y);
	init_set_player(main, 0, 0);
	printf("player after x[%f] y[%f]\n", main->ply.pos_x, main->ply.pos_y);
	return (0);
}

int	init_mlx_hooking(t_main *main)
{
	mlx_hook(main->mlx->win, 2, 1L << 0, &key_press, main);
	mlx_hook(main->mlx->win, 3, 1L << 1, key_release, main);
	// mlx_hook(mlx->win, 4, 0, &actions_mouse, main);
	if (mlx_hook(main->mlx->win, 17, 0, &mlx_free_kill_all, main) == ERROR)// close_window(); yapilacak
		return (ERROR);
	return (0);
}

int	init_mlx_window(t_main *main)
{
	t_mlx	*mlx;

	main->mlx = malloc(sizeof(t_mlx));
	if (main->mlx == NULL)
		return (print_error(PROMPT, "MLX", NULL, strerror(errno)));
	mlx = main->mlx;
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (print_error(PROMPT, "MLX", "mlx_init()", "error."));
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (mlx->win == NULL)
		return (print_error(PROMPT, "MLX", "mlx_new_window()", "error."));
	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_W, WINDOW_H);
	if (mlx->img.ptr == NULL)
		return (print_error(PROMPT, "MLX", "mlx_new_image()", "error."));
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (print_error(PROMPT, "MLX", "mlx_get_data_addr()", "error."));
	return (0);
}

int	init_cub3d(t_main *main)
{
	main = malloc(sizeof(t_main));
	if (main == NULL)
		return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	// printf("key.value[%d]\n", main.key->value);
	return (0);
}

int	init_all(t_main *main)
{
	if (init_cub3d(main) == ERROR)// malloc init area
		return (ERROR);
	// printf("key.value'in adresi %d\n", main->key.value);
	if (init_mlx_window(main) == ERROR)// malloc & image init area
		return (ERROR);
	if (init_mlx_hooking(main) == ERROR)// key, mouse, click hooking area
		return (ERROR);
	if (init_mlx_draw(main) == ERROR)// ply_location...
		return (ERROR);
	return (0);
}