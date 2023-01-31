/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:18:29 by gsever            #+#    #+#             */
/*   Updated: 2023/01/31 12:37:45 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_text_on_window_part2(t_main *main)
{
	char	*tmp;

	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 160,
		WINDOW_H - 170, COLOR_TUNDORA, "FPS:");
	tmp = ft_itoa((int)main->time.fps);
	mlx_string_put(main->mlx.ptr, main->mlx.win, WINDOW_W - 130,
		WINDOW_H - 170, COLOR_TUNDORA, tmp);
	free(tmp);
}

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
	draw_text_on_window_part2(main);
}

/**
 * @brief We send as many ray as the width value of our window.
 * 
	// draw_player_directory(main);// player's rotation_angle (one line).

		// if ((int)main->ply.rotation_angle == (int)angle)
					or
		// if (angle > main->ply.rotation_angle - 10
			&& angle < main->ply.rotation_angle)
					or
		// raycasting(main, main->ply.rotation_angle, (FOV_THICKNESS - 1)/2);
 * 
 * @param main 
 * @fn draw_minimap(): Drawing minimap for clearly see all parts.
 * @fn draw_background(): Drawing screen_height/2 -> half, Ceil and Floor color
 * @fn raycasting(): Sending one ray for calculate and
 *  draw one column to the screen.
 * @fn draw_player_position(): On minimap, drawing small red small square for
 *  player's location.
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
	if (main->loop_count % 20 == 0)
		main->xpm_number_sprite_m++;
	if (main->xpm_number_sprite_m >= TEXTURE_N + 14)
		main->xpm_number_sprite_m = TEXTURE_N + 1;
	while (ray_count < FOV_THICKNESS)
	{
		main->sprite.distance = 0;
		if (angle <= 0.0)
			angle += 360.0;
		else if (angle >= 360.0)
			angle -= 360.0;
		raycasting(main, angle, ray_count);
		angle += (double)FOV / (double)FOV_THICKNESS;
		ray_count++;
	}
	if (main->key.show_mini_map == true)
		draw_player_position(main);
}

/**
 * @brief Main loop area;
 * 
	// static int	loop_count;
	// printf(GREEN"Loop Count:%d\n"END, loop_count++);
 * 
 * 	// printf("player x[%f] y[%f]", main->ply.pos_x, main->ply.pos_y);
	// printf("ply.rotation_angle[%f]\n", main->ply.rotation_angle);
 * 
 * @param main 
 * @fn open_help_page(): Writing a few information.
 * @fn update_player_all(): Setting new calculated player position.
 * @fn draw_with_ray_casting(): Calculating player to wall distance and render.
 * @fn mlx_put_image_to_window(): Putting drawed image to window.
 * @fn draw_text_on_window(): Player; pos_x, pos_y, rotation_angle. Value print
 * @return int 
 */
int	ft_loop(t_main *main)
{
	if (main->key.help_page == true)
		open_help_page(main);
	else
	{
		main->loop_count++;
		if (main->loop_count >= INT_MAX)
			main->loop_count = 50;
		main->is_hit_val = '\0';
		get_or_print_time_for_fps(main, false);
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
		get_or_print_time_for_fps(main, true);
		draw_text_on_window(main);
	}
	return (0);
}

/**
 * @brief MLX: HOOK: funcs().
 * 
 * @param main 
 * @fn mlx_loop_hook(): Like while(1).
 * @fn ft_loop(): After the initializing func()s, cub3D loop.
 * @fn mlx_hook(): For getting hooking possibilities.
 * @fn key_press(): When pressing key from keyboard.
 * @fn key_release(): When releasing key from keyboard.
 * @fn ft_exit(): When clicking red close button top left window.
 * @fn mouse_move(): It works when you move your mouse.
 * @fn mlx_loop(): MLX's automatically data loop.(I think so...)
 * @return int 
 */
int	draw_mlx_window(t_main *main)
{
	mlx_loop_hook(main->mlx.ptr, ft_loop, main);
	mlx_hook(main->mlx.win, 2, (1L << 0), &key_press, main);
	mlx_hook(main->mlx.win, 3, (1L << 1), &key_release, main);
	mlx_hook(main->mlx.win, 17, (0L), &ft_exit, main);
	mlx_hook(main->mlx.win, 6, (0L), &mouse_move, main);
	mlx_loop(main->mlx.ptr);
	return (0);
}
