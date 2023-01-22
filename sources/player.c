/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:05:27 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 17:05:17 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_player_all(t_main *main)
{
	if (main->key.value & GO_FORWARD)
		player_move(main, GO_FORWARD, 1.0);
	if (main->key.value & GO_BACKWARD)
		player_move(main, GO_BACKWARD, -1.0);
	if (main->key.value & GO_RIGHT)
		player_move(main, GO_RIGHT, 1.0);
	if (main->key.value & GO_LEFT)
		player_move(main, GO_LEFT, -1.0);
	if (main->key.value & TURN_RIGHT)
		player_turn(main, TURN_RIGHT, 1.0);
	if (main->key.value & TURN_LEFT)
		player_turn(main, TURN_LEFT, -1.0);
	if (main->key.value & TURN_UP)
		player_turn(main, TURN_UP, 1.0);
	if (main->key.value & TURN_DOWN)
		player_turn(main, TURN_DOWN, -1.0);
}

/**
 * @brief Set the player default pos object
 * 
 * When user press R key from keyboard working here.
 * @param main 
 */
void	set_player_default_pos(t_main *main)
{
	main->ply.pos_x = main->ply.default_pos_x;
	main->ply.pos_y = main->ply.default_pos_y;
	main->ply.rotation_angle = main->ply.default_rotation_angle;
	main->key.screen_mid = (double)(WINDOW_H / 2);
}

/**
 * @brief Saving player's starting positions. Preparing data for R key.
 * 
 * @param main 
 * @param x 
 * @param y 
 */
void	save_player_default_location(t_main *main, int x, int y)
{
	main->ply.default_rotation_angle = main->ply.rotation_angle;
	main->ply.pos_x = (double)x + 0.5;
	main->ply.default_pos_x = (double)x + 0.5;
	main->ply.pos_y = (double)y + 0.5;
	main->ply.default_pos_y = (double)y + 0.5;
}

void	init_set_player(t_main *main, int x, int y)
{
	y = -1;
	while (main->map.map[++y])
	{
		x = -1;
		while (main->map.map[y][++x])
		{
			if (ft_strchr("ENWS", main->map.map[y][x]))
			{
				if (main->map.map[y][x] == 'E')
					main->ply.rotation_angle = 0;
				else if (main->map.map[y][x] == 'N')
					main->ply.rotation_angle = 90;
				else if (main->map.map[y][x] == 'W')
					main->ply.rotation_angle = 180;
				else if (main->map.map[y][x] == 'S')
					main->ply.rotation_angle = 270;
				main->map.map[y][x] = '0';
				save_player_default_location(main, x, y);
				return ;
			}
		}
	}
}
