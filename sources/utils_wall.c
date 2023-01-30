/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:53:55 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 23:46:46 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	next_step_is_wall(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	if (x < 0 || x > main->map.max_x || y < 0 || y > main->map.max_y)
		return (1);
	x_x = floor(x);
	y_y = floor(y);
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)
		return (0);
	return (1);
}

int	is_wall(t_main *main, double x, double y, double angle)
{
	int	x_x;
	int	y_y;

	if (x < 0 || x > main->map.max_x || y < 0 || y > main->map.max_y)
		return (1);
	x_x = floor(x);
	y_y = floor(y);
	if (main->key.door_open_command == true
		&& (int)main->ply.rotation_angle == (int)angle)
	{
		if (ft_strchr("O", main->map.map[y_y][x_x]))
		{
			if (!((int)floor(main->ply.pos_x) == x_x
					&& (int)floor(main->ply.pos_y) == y_y)
				&& (main->map.map[y_y][x_x] == 'O'))
				main->map.map[y_y][x_x] = 'C';
			printf(RED"Door Closed: map[%d][%d]=%c,\
ray_hit_location[x:%f][y:%f]\n"END, x_x, y_y,
				main->map.map[y_y][x_x], x, y);
			main->key.door_open_command = false;
		}
	}
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)
		return (0);
	return (1);
}

int	is_wall_v2(t_main *main, double x, double y, double angle)
{
	int	x_x;
	int	y_y;

	x_x = (int)floor(x);
	y_y = (int)floor(y);
	if (ft_strchr("MZ", main->map.map[y_y][x_x]))
	{
		if (main->key.door_open_command == true
			&& (int)main->ply.rotation_angle == (int)angle)
			printf(CYAN"Passed Inside Sprite: map[%d][%d]=%c,\
ray_hit_location[x:%f][y:%f]\n"END, x_x, y_y, main->map.map[y_y][x_x], x, y);
		main->sprite.pos_x = x_x + 0.5;
		main->sprite.pos_y = y_y + 0.5;
		main->sprite.distance = sqrt(
				powf(main->ply.pos_x - main->sprite.pos_x, 2)
				+ powf(main->ply.pos_y - main->sprite.pos_y, 2));
		if (main->map.map[y_y][x_x] == 'M')
		{
			main->is_hit_val = 'M';
		}
		else if (main->map.map[y_y][x_x] == 'Z')
			main->is_hit_val = 'Z';
		main->sprite.is_hit = true;
	}
	return (ft_strchr(MAP_RAY_CAN_GO, main->map.map[y_y][x_x]) == NULL);
}
