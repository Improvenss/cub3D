/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:01:57 by gsever            #+#    #+#             */
/*   Updated: 2023/01/31 14:37:06 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_ray_part2(t_main *main, double angle, int ray_count)
{
	while (1)
	{
		if (!is_wall(main, main->ray.pos_x, main->ray.pos_y, angle)
			&& (sqrt(pow(main->ply.pos_x - main->ray.pos_x, 2)
					+ pow(main->ply.pos_y - main->ray.pos_y, 2))
				<= main->ray.original_distance))
		{
			if (main->key.show_mini_map == true)
				main->mini_map.addr[(BOX_SIZE * (main->map.max_x + 1))
					* (int)floor(BOX_SIZE * main->ray.pos_y)
					+ (int)floor(BOX_SIZE * main->ray.pos_x)] = COLOR_GREEN;
		}
		else
		{
			if ((int)floor(main->ply.rotation_angle) == (int)floor(angle))
				check_door_info(main, main->ray.pos_x, main->ray.pos_y);
			check_which_texture_put(main, main->ray.pos_x, main->ray.pos_y);
			main->ray.pos_x -= main->ray.next_ray_step_x;
			main->ray.pos_y -= main->ray.next_ray_step_y;
			three_dimension(main, ray_count);
			break ;
		}
		main->ray.pos_x += main->ray.next_ray_step_x;
		main->ray.pos_y += main->ray.next_ray_step_y;
	}
}

/**
 * @brief Minimap's ray's and 3D renders print func().
 * 
 * @param main 
 * @param angle 
 * @param ray_count 
 */
static void	draw_ray(t_main *main, double angle, int ray_count)
{
	main->ray.pos_x = main->ply.pos_x;
	main->ray.pos_y = main->ply.pos_y;
	main->ray.hit_x = main->ray.distance
		* fabs(cos(angle * ONE_DEGREE)) * main->ray.dir_x;
	main->ray.hit_y = main->ray.distance
		* fabs(sin(angle * ONE_DEGREE)) * main->ray.dir_y;
	main->ray.next_ray_step_x = main->ray.hit_x / (WINDOW_H / 2);
	main->ray.next_ray_step_y = main->ray.hit_y / (WINDOW_H / 2);
	draw_ray_part2(main, angle, ray_count);
}

static void	calculate_sprite_values(t_main *main, double angle)
{
	main->sprite.value = 0;
	main->sprite.angle = atan2(fabs(main->ply.pos_y - main->sprite.pos_y),
			fabs(main->ply.pos_x - main->sprite.pos_x)) * ONE_RADIAN;
	if ((main->ray.dir_x > 0 && main->ray.dir_y > 0)
		|| (main->ray.dir_x < 0 && main->ray.dir_y < 0))
		main->sprite.angle = (180.0 - main->sprite.angle);
	if (angle > main->sprite.angle)
	{
		main->sprite.angle = angle - main->sprite.angle;
		main->sprite.length = tan(main->sprite.angle * ONE_DEGREE)
			* main->sprite.distance;
		if (main->sprite.length <= 0.5 && main->sprite.length >= -0.5)
			main->sprite.value = 0.5 - main->sprite.length;
	}
	else if (angle < main->sprite.angle)
	{
		main->sprite.angle = main->sprite.angle - angle;
		main->sprite.length = tan(main->sprite.angle * ONE_DEGREE)
			* main->sprite.distance;
		if (main->sprite.length <= 0.5 && main->sprite.length >= -0.5)
			main->sprite.value = main->sprite.length + 0.5;
	}
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	main->ray.dir_x = ((cos(angle * ONE_DEGREE) > 0) * 2) - 1;
	main->ray.dir_y = ((sin(angle * ONE_DEGREE) > 0) * -2) + 1;
	main->ray.is_hit_vertical = false;
	main->ray.is_hit_horizontal = false;
	main->sprite.is_hit = false;
	ray_vertical(main, angle, main->ray.dir_x, main->ray.dir_y);
	ray_horizontal(main, angle, main->ray.dir_x, main->ray.dir_y);
	if (main->ray.distance_v < main->ray.distance_h)
	{
		main->ray.distance = main->ray.distance_v;
		main->ray.hit_h = false;
		main->ray.hit_v = true;
	}
	else
	{
		main->ray.distance = main->ray.distance_h;
		main->ray.hit_h = true;
		main->ray.hit_v = false;
	}
	if (main->sprite.is_hit == true)
		calculate_sprite_values(main, angle);
	main->ray.original_distance = main->ray.distance;
	main->ray.distance = main->ray.distance
		* cos((main->ply.rotation_angle - angle) * ONE_DEGREE);
	draw_ray(main, angle, ray_count);
}
