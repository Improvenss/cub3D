/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_page.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:21:37 by gsever            #+#    #+#             */
/*   Updated: 2023/01/23 00:51:13 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_information(t_main *main)
{
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 200, COLOR_SILVER,
		"Controls: W A S D -> Player Movement");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 180, COLOR_SILVER,
		"Controls: ⬅️ ⬆️ ⬇️ ➡️ -> Player View Point");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 160, COLOR_SILVER, "Reset:	R");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 140, COLOR_SILVER, "Door:	Open/Close:	E");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 120, COLOR_SILVER, "Mouse Control: Space");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 100, COLOR_SILVER, "Close Help: H");
	mlx_string_put(main->mlx.ptr, main->mlx.win, (int)(WINDOW_W / 2) - 100,
		(WINDOW_H / 2) - 80, COLOR_SILVER, "Exit Program: ESC");
}

void	open_help_page(t_main *main)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y <= WINDOW_H)
	{
		x = -1;
		while (++x <= WINDOW_W)
			my_mlx_pixel_put(&main->screen, x, y, COLOR_BLACK);
	}
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->mlx.win, 0, 0);
	draw_information(main);
}
