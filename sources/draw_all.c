/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:18:29 by gsever            #+#    #+#             */
/*   Updated: 2023/01/12 22:56:49 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_text_on_window(t_main *main)
{
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 20, COLOR_TUNDORA, "H - Help");
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 120, COLOR_TUNDORA, ft_itoa((int)main->ply.rotation_angle));
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 140,
		WINDOW_H - 150, COLOR_TUNDORA, "x:");
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 120,
		WINDOW_H - 150, COLOR_TUNDORA, ft_itoa((int)main->ply.pos_x));
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 100,
		WINDOW_H - 150, COLOR_TUNDORA, "x:");
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 150, COLOR_TUNDORA, ft_itoa((int)main->ply.pos_y));
	// mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		// WINDOW_H - 20 - 100, COLOR_TUNDORA, ft_itoa(main->key.value));
}

void	draw_with_ray_casting(t_main *main)
{
	double	angle;
	int		ray_count;

	draw_background(main);// floor and ceil
	draw_minimap(main);
	angle = -1 * (FOV / 2.0);
	ray_count = 0;
	while (angle <= (FOV / 2.0)) // angle: -30º <= 30º -> arasinda 60º
	{
		raycasting(main, main->ply.rotation_angle + angle, ray_count);
		angle += (FOV / 2.0) / (FOV_THICKNESS / 2.0);
		ray_count++;
	}
	draw_player_position(main);// player's red square.
	draw_player_directory(main);// player's rotation_angle (one line).
}

int	ft_loop(t_main *main)
{
	update_player_all(main);
	draw_with_ray_casting(main);
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->screen.ptr, 0, 0);
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->mini_map.ptr, 0, 0);
	draw_text_on_window(main);// txt put to window
	// printf("player x[%f] y[%f]", main->ply.pos_x, main->ply.pos_y);
	// printf("ply.rotation_angle[%f]\n", main->ply.rotation_angle);
	return (0);
}

int	draw_mlx_window(t_main *main)
{
	mlx_loop_hook(main->mlx.ptr, ft_loop, main);
	mlx_hook(main->mlx.win, 2, 1L << 0, &key_press, main);
	mlx_hook(main->mlx.win, 3, 1L << 1, &key_release, main);
	mlx_hook(main->mlx.win, 17, (0L), &ft_exit, main);
	mlx_loop(main->mlx.ptr);
	return (0);
}
