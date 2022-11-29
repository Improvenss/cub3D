/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:14:46 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 17:41:17 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall(double x, double y, t_main *main)
{
	int	xX;
	int	yY;

	if (x < 0 || x > main->max_x || y < 0 || y > main->max_y)
		return (1);
	xX = floor(x);
	yY = floor(y);
	//printf("xX:%d, yY:%d\n", xX, yY);
	if (main->map[yY][xX] != '1')
		return (0);
	return (1);
}

int	update_player(t_main *main)
{
/*
	double newPlayerX = main->ply.x;
	double newPlayerY = main->ply.y;
	int		move_way_value_x = 1;
	int		move_way_value_y = -1;
	
	if (main->key.up != 0)
	{
		newPlayerX = main->ply.x + (main->ply.walkSpeed / main->box_size) * cos(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_x;
		newPlayerY = main->ply.y + (main->ply.walkSpeed / main->box_size) * sin(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_y;
	}
	if (main->key.down != 0)
	{
		newPlayerX = main->ply.x - (main->ply.walkSpeed / main->box_size) * cos(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_x;
		newPlayerY = main->ply.y - (main->ply.walkSpeed / main->box_size) * sin(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_y;
	}
	if (main->key.left != 0)
	{
		newPlayerX = main->ply.x - (main->ply.walkSpeed / main->box_size) * sin(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_x;
		newPlayerY = main->ply.y + (main->ply.walkSpeed / main->box_size) * cos(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_y;
	}
	if (main->key.right != 0)
	{
		newPlayerX = main->ply.x + (main->ply.walkSpeed / main->box_size) * sin(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_x;
		newPlayerY = main->ply.y - (main->ply.walkSpeed / main->box_size) * cos(main->ply.rotationAngle * (M_PI / 180)) * move_way_value_y;
	}
	if (!is_wall(newPlayerX, newPlayerY, main))
	{
		main->ply.x = newPlayerX;
		main->ply.y = newPlayerY;
		printf("	plyr_map x: %f y:%f\n", main->ply.x * main->box_size, main->ply.y * main->box_size);
		printf("	plyr_ x: %f y:%f\n", main->ply.x, main->ply.y);
	}
	*/
	if (main->key_val & GO_FORWARD)
		player_move(main, GO_FORWARD, 1);
	if (main->key_val & GO_BACKWARD)
		player_move(main, GO_BACKWARD, -1);
	if (main->key_val & GO_RIGHT)
		player_move(main, GO_RIGHT, 1);
	if (main->key_val & GO_LEFT)
		player_move(main, GO_LEFT, -1);
	if (main->key_val & TURN_RIGHT)
		player_turn(main, TURN_RIGHT, 1);
	if (main->key_val & TURN_LEFT)
		player_turn(main, TURN_LEFT, -1);
	if (main->key_val & TURN_UP)
		player_turn(main, TURN_UP, 1);
	if (main->key_val & TURN_DOWN)
		player_turn(main, TURN_DOWN, -1);
	printf("rotation_angle: %f\n", main->ply.rotationAngle);
	printf("	plyr_map x: %f y:%f\n", main->ply.x * main->box_size, main->ply.y * main->box_size);
	printf("	plyr_ x: %f y:%f\n", main->ply.x, main->ply.y);
	return (0);
}

int	actions_key_press(int keycode, t_main *main)
{
	/*
	main->key.left = 0;
	main->key.right = 0;
	main->key.up = 0;
	main->key.down = 0;
	if (keycode == KEY_A)
		main->key.left = 1;
	if (keycode == KEY_D)
		main->key.right = 1;
	if (keycode == KEY_W)
		main->key.up = 1;
	if (keycode == KEY_S)
		main->key.down = 1;
	if (keycode == KEY_ARROW_LEFT)
	{
		if (main->ply.rotationAngle == 360)
			main->ply.rotationAngle = PLAYER_ROTATION_SPEED;
		else
			main->ply.rotationAngle = main->ply.rotationAngle + PLAYER_ROTATION_SPEED;
		if (main->ply.rotationAngle == 360)
			main->ply.rotationAngle = 0;
	}
	if (keycode == KEY_ARROW_RIGHT)
	{
		if (main->ply.rotationAngle == 0)
			main->ply.rotationAngle = 360 - PLAYER_ROTATION_SPEED;
		else
			main->ply.rotationAngle = main->ply.rotationAngle - PLAYER_ROTATION_SPEED;
	}
	*/
	if (keycode == KEY_ESC)
		exit(0);//ft_free_and_close(); need add.
	else if (keycode == KEY_W)
		main->key_val |= GO_FORWARD;
	else if (keycode == KEY_S)
		main->key_val |= GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key_val |= GO_RIGHT;
	else if (keycode == KEY_A)
		main->key_val |= GO_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key_val |= TURN_RIGHT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key_val |= TURN_LEFT;
	else if (keycode == KEY_ARROW_UP)
		main->key_val |= TURN_UP;
	else if (keycode == KEY_ARROW_DOWN)
		main->key_val |= TURN_DOWN;
	return (0);
}

int	actions_key_release(int keycode, t_main *main)
{
	if (keycode == KEY_W)
		main->key_val &= ~GO_FORWARD;
	else if (keycode == KEY_S)
		main->key_val &= ~GO_BACKWARD;
	else if (keycode == KEY_D)
		main->key_val &= ~GO_RIGHT;
	else if (keycode == KEY_A)
		main->key_val &= ~GO_LEFT;
	else if (keycode == KEY_ARROW_LEFT)
		main->key_val &= ~TURN_LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		main->key_val &= ~TURN_RIGHT;
	return (0);
}