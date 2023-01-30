/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:10:44 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 09:47:46 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief 
 * 
 * system("leaks cub3D");
	printf("You press a key["B_CYAN"%d"END"]\
		& key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
 * @param keycode 
 * @param main 
 * @return int 
 */
int	key_press(int keycode, t_main *main)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		main->key.value |= GO_FORWARD;
	else if (keycode == KEY_S)
		main->key.value |= GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key.value |= GO_RIGHT;
	else if (keycode == KEY_A)
		main->key.value |= GO_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key.value |= TURN_RIGHT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key.value |= TURN_LEFT;
	else if (keycode == KEY_ARROW_UP)
		main->key.value |= TURN_UP;
	else if (keycode == KEY_ARROW_DOWN)
		main->key.value |= TURN_DOWN;
	else if (keycode == KEY_R)
		set_player_default_pos(main);
	else if (keycode == KEY_L_SHIFT)
		main->ply.walk_speed = PLAYER_WALK_SPEED + 1.50;
	else if (keycode == KEY_E)
		main->key.door_open_command = true;
	return (0);
}

void	key_release_part_2(int keycode, t_main *main)
{
	if (keycode == KEY_H)
		main->key.help_page = !main->key.help_page;
	else if (keycode == KEY_M)
		main->key.show_mini_map = !main->key.show_mini_map;
}

/**
 * @brief 
 * 
 * 	printf("You removed a key["B_BLUE"%d"END"]\
		& key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
 * @param keycode 
 * @param main 
 * @return int 
 */
int	key_release(int keycode, t_main *main)
{
	if (keycode == KEY_W)
		main->key.value &= ~GO_FORWARD;
	else if (keycode == KEY_S)
		main->key.value &= ~GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key.value &= ~GO_RIGHT;
	else if (keycode == KEY_A)
		main->key.value &= ~GO_LEFT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key.value &= ~TURN_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key.value &= ~TURN_RIGHT;
	else if (keycode == KEY_ARROW_UP)
		main->key.value &= ~TURN_UP;
	else if (keycode == KEY_ARROW_DOWN)
		main->key.value &= ~TURN_DOWN;
	else if (keycode == KEY_L_SHIFT)
		main->ply.walk_speed = PLAYER_WALK_SPEED;
	else if (keycode == KEY_SPACE)
		main->mouse.is_enable = !main->mouse.is_enable;
	key_release_part_2(keycode, main);
	return (0);
}

/**
 * @brief Getting mouse's x and y coordinates and setting
 *  after the calculated angle and screen_mid location. :).
 * 
	// mlx_mouse_move(main->mlx.ptr, main->mlx.win,
main->ply.rotation_angle, main->key.screen_mid);
	// printf("mouse pos:[%d]\n", mlx_mouse_get_pos(main->mlx.ptr,
main->mlx.win, mouse_x, mouse_y));
	// mlx_mouse_hide(main->mlx.ptr, main->mlx.win);
	// if (x > 360)
		// mlx_mouse_move(main->mlx.ptr, main->mlx.win, 360, 360);

		// printf("mouse:x[%d] y[%d]\n", x, y);
 * @param x 
 * @param y 
 * @param main 
 * @return int 
 */
int	mouse_move(int x, int y, t_main *main)
{
	if (main->mouse.is_enable)
	{
		main->ply.rotation_angle = -1.0 * (x % 360);
		if (main->ply.rotation_angle < 0.0)
			main->ply.rotation_angle += 360.0;
		else if (main->ply.rotation_angle >= 360.0)
			main->ply.rotation_angle -= 360.0;
		main->key.screen_mid = -1.0 * (y % WINDOW_H);
	}
	return (0);
}
