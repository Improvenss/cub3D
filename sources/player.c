/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:30:18 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 07:53:33 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Left & Right rotation okay but now we are not doing up & down look.
 * 
 * @param main main structure
 * @param way up | down | left | right
 * @param val + or -
 */
void	player_turn(t_main *main, int way, double val)
{
	(void)way;
	main->ply.rotationAngle += val * PLAYER_ROTATION_SPEED;
	if (main->ply.rotationAngle < 0)
		main->ply.rotationAngle = 360;
	else if (main->ply.rotationAngle > 360)
		main->ply.rotationAngle = 0;
	// if (way & (TURN_LEFT | TURN_RIGHT))
	// 	main->ply.rotationAngle += val * PLAYER_ROTATION_SPEED / 10;
	// if (main->ply.rotationAngle <= 0)
	// 	main->ply.rotationAngle = 360 - PLAYER_ROTATION_SPEED / 10;
	// if (main->ply.rotationAngle == 360)
	// 	main->ply.rotationAngle = 0;
}

/**
 * @brief W A S D steps for playeer.
 * 
 * @param main 
 * @param way 
 */
void	player_move(t_main *main, int way, double val)
{
	double	last_location_x;
	double	last_location_y;

	last_location_x = main->ply.x;
	last_location_y = main->ply.y;
	if (way & (GO_FORWARD | GO_BACKWARD))
	{
		main->ply.x += val * (main->ply.x * PLAYER_WALKSPEED / 10000);//bu okay ama karakter nereye bakiyorsa oraya dogru ilerlemiyor
		// main->ply.x -= val * (PLAYER_WALKSPEED / main->box_size) * cos(main->ply.rotationAngle * (M_PI / 180));
		if (is_wall(main->ply.x, main->ply.y, main))
			main->ply.x = last_location_x;
		main->ply.y += val * (main->ply.y * PLAYER_WALKSPEED / 10000);//bu okay ama karakter nereye bakiyorsa oraya dogru ilerlemiyor
		// main->ply.y -= val * (PLAYER_WALKSPEED / main->box_size) * sin(main->ply.rotationAngle * (M_PI / 180));
		if (is_wall(main->ply.x, main->ply.y, main))
			main->ply.y = last_location_y;
	}
	else if (way & (GO_LEFT | GO_RIGHT))
	{
		main->ply.x -= val * (main->ply.y * PLAYER_WALKSPEED / 10000);
		if (is_wall(main->ply.x, main->ply.y, main))
			main->ply.x = last_location_x;
		main->ply.y += val * (main->ply.x * PLAYER_WALKSPEED / 10000);
		if (is_wall(main->ply.x, main->ply.y, main))
			main->ply.y = last_location_y;
	}
}