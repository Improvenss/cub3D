/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:53:08 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 17:05:22 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Left & Right rotation okay but now we are not doing up & down look.
 * 
 * @param main main structure
 * @param way up | down | left | right -> bitwise val.
 * @param val + or -
 */
void	player_turn(t_main *main, int way, double val)
{
	if (way & (TURN_LEFT | TURN_RIGHT))
		main->ply.rotation_angle -= val * PLAYER_ROTATION_SPEED;
	if (main->ply.rotation_angle < 0)
		main->ply.rotation_angle = 360;
	else if (main->ply.rotation_angle > 360)
		main->ply.rotation_angle = 0;
	if (way & (TURN_UP | TURN_DOWN))
		main->key.screen_mid += (int)val * 10;
	if (main->key.screen_mid < 0)
		main->key.screen_mid = 0;
	else if (main->key.screen_mid > WINDOW_H)
		main->key.screen_mid = WINDOW_H;
}

/**
 * @brief W A S D steps for player.
 */
void	player_move(t_main *main, int way, double val)
{
	main->ply.last_location_x = main->ply.pos_x;
	main->ply.last_location_y = main->ply.pos_y;
	if (way & (GO_FORWARD | GO_BACKWARD))
	{
		main->ply.pos_x += val * ((main->ply.walk_speed / BOX_SIZE)
				* cos(main->ply.rotation_angle * ONE_DEGREE));
		if (next_step_is_wall(main, main->ply.pos_x, main->ply.pos_y))
			main->ply.pos_x = main->ply.last_location_x;
		main->ply.pos_y -= val * ((main->ply.walk_speed / BOX_SIZE)
				* sin(main->ply.rotation_angle * ONE_DEGREE));
		if (next_step_is_wall(main, main->ply.pos_x, main->ply.pos_y))
			main->ply.pos_y = main->ply.last_location_y;
	}
	if (way & (GO_LEFT | GO_RIGHT))
	{
		main->ply.pos_x += val * ((main->ply.walk_speed / BOX_SIZE)
				* sin(main->ply.rotation_angle * ONE_DEGREE));
		if (next_step_is_wall(main, main->ply.pos_x, main->ply.pos_y))
			main->ply.pos_x = main->ply.last_location_x;
		main->ply.pos_y += val * ((main->ply.walk_speed / BOX_SIZE)
				* cos(main->ply.rotation_angle * ONE_DEGREE));
		if (next_step_is_wall(main, main->ply.pos_x, main->ply.pos_y))
			main->ply.pos_y = main->ply.last_location_y;
	}
}
