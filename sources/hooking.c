/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 02:10:44 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 00:00:07 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_main *main)
{
	if (keycode == KEY_ESC)
	{
		// system("leaks cub3D");
		exit(0);//ft_free_and_close(); need add.
	}
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
	// printf("You press a key["B_CYAN"%d"END"]
	// & key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
	return (0);
}

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
		main->mouse.is_enable = !main->mouse.is_enable;// or--> main->mouse.is_enable = main->mouse.is_enable ? false : true;
	// else if (keycode == KEY_E)
		// main->key.door_open_command = false;
	// printf("You removed a key["B_BLUE"%d"END"]\
	// & key.value["B_YELLOW"%d"END"]\n", keycode, main->key.value);
	return (0);
}

int	mouse_move(int x, int y, t_main *main)
{
	// int	*mouse_x = 0;
	// int	*mouse_y = 0;
	if (main->mouse.is_enable)
	{
		// mlx_mouse_move(main->mlx.ptr, main->mlx.win, main->ply.rotation_angle, main->key.screen_mid);
		// printf("mouse pos:[%d]\n", mlx_mouse_get_pos(main->mlx.ptr, main->mlx.win, mouse_x, mouse_y));
		main->ply.rotation_angle = -1.0 * (x % 360);
		main->key.screen_mid = -1.0 * (y % WINDOW_H);
		// printf("mouse:x[%d] y[%d]\n", x, y);
	}
	return (0);
}