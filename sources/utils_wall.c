/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:53:55 by gsever            #+#    #+#             */
/*   Updated: 2023/01/25 23:19:11 by gsever           ###   ########.fr       */
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
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)// playerimizin konumu icin genellikle
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
	if (ft_strchr("MZ", main->map.map[y_y][x_x])
		&& main->sprite.is_hit == false)// M'yi de sonra ekleriz
	{
		if (main->key.door_open_command == true
			&& (int)main->ply.rotation_angle == (int)angle)
			printf("Passed Inside Sprite: map[%d][%d]=%c,\
ray_hit_location[x:%f][y:%f]\n", x_x, y_y, main->map.map[y_y][x_x], x, y);
		// static int	times_entered;
		// printf("x: %f, y: %f, floor_x: %d, floor_y: %d\n", x, y, x_x, y_y);
		// printf("Z spritinin icine vurduk[%d]\n", times_entered++);// 800 tane isinimiz 1'er kere giriyor yani her isin 1 kere giriyor OK.
		main->sprite.is_hit = true;// Buradaki true/false sayesinde. 1 kere yazdiracak printf'le.
	}
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
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)// playerimizin konumu icin genellikle
		return (0);
	return (1);
}

int is_wall_v2(t_main *main, double x, double y, int status, int dir_x, int dir_y)
{
	int x_x;
	int y_y;

	x_x = (int)floor(x);
	y_y = (int)floor(y);
	if (ft_strchr("Z", main->map.map[y_y][x_x]))
	{
		if (status == VERTICAL && main->sprite.is_sprite_ray_vertical == false)
		{
			x = x + 0.0001*dir_x;
			// printf("dir_y:%d\n", dir_y);
			main->sprite.dist_v =  sqrt(((main->ply.pos_x - x)*(main->ply.pos_x - x)) + ((main->ply.pos_y - y)*(main->ply.pos_y - y)));
			if (dir_y > 0)// yani + ise.
			{
				main->sprite.oran_v = y - floor(y);
				// printf("vertical\n");
				// printf("oran_v:%f\n", main->sprite.oran_v);
			}
			else if (dir_y < 0)// yani - ise.
			{
				main->sprite.oran_v = ceil(y) - y;
				main->sprite.oran_v = 1 - main->sprite.oran_v;
				// printf("vertical\n");
				// printf("oran_v:%f\n", main->sprite.oran_v);
			}
			main->sprite.is_sprite_ray_vertical = true;
		}
		if (status == HORIZONTAL && main->sprite.is_sprite_ray_horizontal == false)
		{
			y = y + 0.0001*dir_y;
			main->sprite.dist_h =  sqrt(((main->ply.pos_x - x)*(main->ply.pos_x - x)) + ((main->ply.pos_y - y)*(main->ply.pos_y - y)));
			if (dir_x < 0)// yani + ise.
			{
				main->sprite.oran_h = ceil(x) - x;
				main->sprite.oran_h = 1 - main->sprite.oran_h;
				// printf("oran_h:%f\n", main->sprite.oran_h);
				// printf("-x:%f, sprite.oran:%f, oran_h:%f\n", x, main->sprite.oran, main->sprite.oran_h);
			}
			else if (dir_x > 0)// yani - ise.
			{
				main->sprite.oran_h = x - floor(x);
				// printf("oran_h:%f\n", main->sprite.oran_h);
			}
			main->sprite.is_sprite_ray_horizontal = true;
		}
		if (main->sprite.distance == 0)
		{
			main->sprite.pos_x = x_x + 0.5;
			main->sprite.pos_y = y_y + 0.5;
			main->sprite.distance = sqrt(((main->ply.pos_x - main->sprite.pos_x)*(main->ply.pos_x - main->sprite.pos_x)) + ((main->ply.pos_y - main->sprite.pos_y)*(main->ply.pos_y - main->sprite.pos_y)));
		}
	}
	// return (ft_strchr("0NSEWZ", main->map.map[y_y][x_x]) == NULL);
	return (ft_strchr(MAP_RAY_CAN_GO, main->map.map[y_y][x_x]) == NULL);// isinimiz bunlarin icinden gecebilir, haricindekilerden gecemez//return (ft_strchr("0NSEWMZ", main->map.map[y_y][x_x]) == NULL);
}