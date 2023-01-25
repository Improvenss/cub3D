/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:18:29 by gsever            #+#    #+#             */
/*   Updated: 2023/01/25 23:21:25 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_text_on_window(t_main *main)
{
	char	*tmp;

	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 20, COLOR_TUNDORA, "H - Help");
	tmp = ft_itoa((int)main->ply.rotation_angle);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 120, COLOR_TUNDORA, tmp);
	free(tmp);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 140,
		WINDOW_H - 150, COLOR_TUNDORA, "x:");
	tmp = ft_itoa((int)main->ply.pos_x);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 120,
		WINDOW_H - 150, COLOR_TUNDORA, tmp);
	free(tmp);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 100,
		WINDOW_H - 150, COLOR_TUNDORA, "y:");
	tmp = ft_itoa((int)main->ply.pos_y);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 80,
		WINDOW_H - 150, COLOR_TUNDORA, tmp);
	free(tmp);
}

/**
 * @brief 
 * 
	// draw_player_directory(main);// player's rotation_angle (one line).

		// if ((int)main->ply.rotation_angle == (int)angle)
 * 
 * @param main 
 */
void	draw_with_ray_casting(t_main *main)
{
	double	angle;
	int		ray_count;

	if (main->key.show_mini_map == true)
		draw_minimap(main);
	draw_background(main);
	angle = main->ply.rotation_angle - (FOV / 2.0);
	ray_count = 0;
	main->sprite.distance = 0;
	while (ray_count < FOV_THICKNESS)
	{
		// if ((int)main->ply.rotation_angle == (int)angle)
			raycasting(main, angle, ray_count);
		angle += (double)FOV / (double)FOV_THICKNESS;
		ray_count++;
	}
	if (main->key.show_mini_map == true)
		draw_player_position(main);
}

/**
 * @brief 
 * 
 * 	// printf("player x[%f] y[%f]", main->ply.pos_x, main->ply.pos_y);
	// printf("ply.rotation_angle[%f]\n", main->ply.rotation_angle);
 * 
 * @param main 
 * @return int 
 */
int	ft_loop(t_main *main)
{
	// static int	loop_count;
	// printf("Loop Count:%d\n", loop_count++);
	if (main->key.help_page == true)
		open_help_page(main);
	else
	{
		update_player_all(main);
		draw_with_ray_casting(main);
		mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
			main->screen.ptr, 0, 0);
		if (main->key.show_mini_map == true)
			mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
				main->mini_map.ptr, 0, 0);
		mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
			main->xpm[7].img.ptr, ((WINDOW_W / 2) - main->xpm[7].width / 2),
			((WINDOW_H / 2) - main->xpm[7].height / 2));
		draw_text_on_window(main);
	}
	return (0);
}

int	draw_mlx_window(t_main *main)
{
	mlx_loop_hook(main->mlx.ptr, ft_loop, main);
	mlx_hook(main->mlx.win, 2, 1L << 0, &key_press, main);
	mlx_hook(main->mlx.win, 3, 1L << 1, &key_release, main);
	mlx_hook(main->mlx.win, 17, (0L), &ft_exit, main);
	mlx_hook(main->mlx.win, 6, (0L), &mouse_move, main);
	mlx_loop(main->mlx.ptr);
	return (0);
}
