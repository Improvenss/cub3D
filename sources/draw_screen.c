/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:01:57 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 11:32:49 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Drawing Ceil and Floor color to screen.
 * 
	//White RGB code = 255*65536+255*256+255 = #FFFFFF
 * 
	// main->screen.addr[WINDOW_W * y + x] = ceil;
	// main->screen.addr[WINDOW_W * y + x] = floor;
 * @param main 
 * @fn my_mlx_pixel_put(): For Ceil; Half up height filling .cub's ceil color.
 * @fn my_mlx_pixel_put(): For Floor; Half down height
 *  filling .cub's floor color.
 */
void	draw_background( t_main *main)
{
	int	y;
	int	x;
	int	ceil;
	int floor;

	ceil = (main->texture.rgb_c[0] * 65536)
		+ (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];
	y = -1;
	while (++y < main->key.screen_mid)
	{
		x = -1;
		while (++x < WINDOW_W)
			my_mlx_pixel_put(&main->screen, x, y, ceil);
	}
	floor = (main->texture.rgb_f[0] * 65536)
		+ (main->texture.rgb_f[1] * 256) + main->texture.rgb_f[2];
	while (y++ < WINDOW_H)
	{
		x = -1;
		while (++x < WINDOW_W)
			my_mlx_pixel_put(&main->screen, x, y, floor);
	}
}

/**
 * @brief Drawing(rendering) like 3D to the screen.
 * 
 * @param main 
 * @param ray_count main->screen img's ray number.
 */
void _3D(t_main *main, int ray_count)
{
	int	loc;
	int	oran;

	main->ray.distance = main->ray.distance * (double)BOX_SIZE
		* ((double)WINDOW_H / (double)WINDOW_W);
	loc = (WINDOW_W * main->key.screen_mid) - ray_count;
	oran = (((double)WINDOW_H / 2.0) / main->ray.distance) * (double)BOX_SIZE;
	if (oran > 4000)
		oran = 4000;
	draw_xpm_to_wall(main, loc, oran, main->xpm[main->xpm_number]);
	if ((main->ray.original_distance > main->sprite.distance)
		&& main->sprite.is_hit == true)// sprite'nin duvarin arkasindayken de gozukmesini engelliyor
			draw_xpm_to_sprite(main, loc, main->xpm[5]);
}

/**
 * @brief Minimap's ray's and 3D renders print func().
 * 
 * @param main 
 * @param angle 
 * @param ray_count 
 */
void draw_ray(t_main *main, double angle, int ray_count)
{
	main->ray.pos_x = main->ply.pos_x;
	main->ray.pos_y = main->ply.pos_y;
	main->ray.hit_x = main->ray.distance
		* fabs(cos(angle * ONE_DEGREE)) * main->ray.dir_x;
	main->ray.hit_y = main->ray.distance
		* fabs(sin(angle * ONE_DEGREE)) * main->ray.dir_y;
	main->ray.next_ray_step_x = main->ray.hit_x / (WINDOW_H / 2);
	main->ray.next_ray_step_y = main->ray.hit_y / (WINDOW_H / 2);
	while (1)
	{
		int	is_wall_ret_val = -1;
		is_wall_ret_val = is_wall(main, main->ray.pos_x, main->ray.pos_y, angle);
		// if (!is_wall(main, main->ray.pos_x, main->ray.pos_y, angle)
		if (is_wall_ret_val == 0 && (sqrt(((main->ply.pos_x - main->ray.pos_x)
						* (main->ply.pos_x - main->ray.pos_x))
					+ ((main->ply.pos_y - main->ray.pos_y)
						* (main->ply.pos_y - main->ray.pos_y)))
				<= main->ray.original_distance))
		{
			if (main->key.show_mini_map == true)
				main->mini_map.addr[(BOX_SIZE * (main->map.max_x + 1))
					* (int)floor(BOX_SIZE * main->ray.pos_y)
					+ (int)floor(BOX_SIZE * main->ray.pos_x)] = COLOR_GREEN;
		}
		else if (is_wall_ret_val == 1)
		{
			if ((int)floor(main->ply.rotation_angle) == (int)floor(angle))
			{
				check_door_open_or_close(main, main->ray.pos_x,
					main->ray.pos_y);
			}
			check_which_texture_put(main, main->ray.pos_x, main->ray.pos_y);
			main->ray.pos_x -= main->ray.next_ray_step_x;
			main->ray.pos_y -= main->ray.next_ray_step_y;
			_3D(main, ray_count);
			break;
		}
		main->ray.pos_x += main->ray.next_ray_step_x;
		main->ray.pos_y += main->ray.next_ray_step_y;
	}
}

void	calculate_sprite_values(t_main *main, double angle)
{
	main->sprite.value = 0;
	main->sprite.angle = atan2(fabs(main->ply.pos_y - main->sprite.pos_y), fabs(main->ply.pos_x - main->sprite.pos_x)) * ONE_RADIAN; // doğru değere sahip
	if ((main->ray.dir_x > 0 && main->ray.dir_y > 0) || (main->ray.dir_x < 0 && main->ray.dir_y < 0))
		main->sprite.angle = (180.0 - main->sprite.angle);
	// if (main->ply.pos_y >= main->sprite.pos_y + 0.5)
	// {
		if (angle > main->sprite.angle)
		{
			main->sprite.angle = angle - main->sprite.angle;
			main->sprite.length = tan(main->sprite.angle * ONE_DEGREE) * main->sprite.distance;
			if (main->sprite.length <= 0.5 && main->sprite.length >= -0.5)
				main->sprite.value = 0.5 - main->sprite.length;
		}
		else if (angle < main->sprite.angle)
		{
			main->sprite.angle = main->sprite.angle - angle;
			main->sprite.length = tan(main->sprite.angle * ONE_DEGREE) * main->sprite.distance;
			if (main->sprite.length <= 0.5 && main->sprite.length >= -0.5)
				main->sprite.value = main->sprite.length + 0.5;
		}
	// }
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	main->ray.dir_x = ((cos(angle * ONE_DEGREE) > 0) * 2) - 1;
	main->ray.dir_y = ((sin(angle * ONE_DEGREE) > 0) * -2) + 1;
	main->ray.is_hit_vertical = false;
	main->ray.is_hit_horizontal = false;
	main->sprite.is_hit = false;
	ray_vertical(main, angle, main->ray.dir_x, main->ray.dir_y); //dikey
	ray_horizontal(main, angle, main->ray.dir_x, main->ray.dir_y); //yatay
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
	main->ray.original_distance = main->ray.distance;//minimap's kacan isinlari icin
	main->ray.distance = main->ray.distance * cos((main->ply.rotation_angle - angle) * ONE_DEGREE);// balik gozunu engellemek icin.
	draw_ray(main, angle, ray_count);
}