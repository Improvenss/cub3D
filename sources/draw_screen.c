/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:01:57 by gsever            #+#    #+#             */
/*   Updated: 2023/01/25 23:19:58 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background( t_main *main)
{
//White RGB code = 255*65536+255*256+255 = #FFFFFF        başına bitanadaha koy şaffaflığ ıçın
	int	y = 0;
	int	x = 0;
	int ceil = (main->texture.rgb_c[0] * 65536) + (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];
	int floor = (main->texture.rgb_f[0] * 65536) + (main->texture.rgb_f[1] * 256) + main->texture.rgb_f[2];
//	printf("ceil: %d floor: %d\n", ceil, floor);
	// while (y < WINDOW_H / 2)
	// printf("main->key.screen_mid: %d\n", main->key.screen_mid);
	while (y < main->key.screen_mid)// int ve double !!!!!!!!!!!!!!!
	{
		x = 0;
		while (x < WINDOW_W)
		{
			// main->screen.addr[WINDOW_W * y + x] = ceil;
			my_mlx_pixel_put(&main->screen, x, y, ceil);
			x++;
		}
		y++;
	}
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
		{
			// main->screen.addr[WINDOW_W * y + x] = floor;
			my_mlx_pixel_put(&main->screen, x, y, floor);
			x++;
		}
		y++;
	}
}

// void	draw_square_n_s_e_w()

void _3D(t_main *main, int ray_count)
{
	int loc;
	int oran;
	main->ray.distance = main->ray.distance * (double)BOX_SIZE
		* ((double)WINDOW_H / (double)WINDOW_W);
	loc = (WINDOW_W * main->key.screen_mid) - ray_count;
	oran = (((double)WINDOW_H / 2.0) / main->ray.distance) * (double)BOX_SIZE;
	if (oran > 4000)
		oran = 4000;
	if (main->xpm_number == -1)
	{
		if (main->ray.hit_h == true && main->ray.dir_y == -1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[0]);
		else if (main->ray.hit_h == true && main->ray.dir_y == 1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[1]);
		else if (main->ray.hit_v == true && main->ray.dir_x == 1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[2]);
		else if (main->ray.hit_v == true && main->ray.dir_x == -1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[3]);
	}
	else
	{
		// printf("main->xpm_number[%d]\n", main->xpm_number);
		if (main->ray.hit_h == true && main->ray.dir_y == -1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[main->xpm_number]);
		else if (main->ray.hit_h == true && main->ray.dir_y == 1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[main->xpm_number]);
		else if (main->ray.hit_v == true && main->ray.dir_x == 1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[main->xpm_number]);
		else if (main->ray.hit_v == true && main->ray.dir_x == -1)
			draw_xpm_to_wall(main, loc, oran, main->xpm[main->xpm_number]);
	}

	if (main->ray.original_distance > main->sprite.distance)
	{
		if (main->sprite.is_sprite_ray_horizontal == true || main->sprite.is_sprite_ray_vertical == true)
		{
			// printf("s_dist:%f\n", main->sprite.distance);
			// printf("w_dist:%f\n", main->ray.distance);
			draw_xpm_to_sprite(main, loc, main->xpm[5]);
		}
	}
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
	main->sprite.is_hit = false;// Isinimiz daha herhangi bir sprite'ye carpmadi.
	main->ray.next_ray_step_x = main->ray.hit_x / (WINDOW_H / 2);
	main->ray.next_ray_step_y = main->ray.hit_y / (WINDOW_H / 2);
	while (1)
	{
		int	is_wall_ret_val = -1;
		is_wall_ret_val = is_wall(main, main->ray.pos_x, main->ray.pos_y, angle);
		// printf("is_wall_ret_val[%d]\n", is_wall_ret_val);
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
				// printf("rotation: %f, angle: %f\n\n", main->ply.rotation_angle, angle);
				// printf("rotation: %d, angle: %d\n", (int)floor(main->ply.rotation_angle), (int)floor(angle));
				check_door_open_or_close(main, main->ray.pos_x,
					main->ray.pos_y);
			}
			check_which_texture_put(main, main->ray.pos_x, main->ray.pos_y);
			main->ray.pos_x -= main->ray.next_ray_step_x;
			main->ray.pos_y -= main->ray.next_ray_step_y;
			// printf("cizdirdikten onceki pos_x: %f\n", main->ray.pos_x);
			// printf("cizdirdikten onceki pos_y: %f\n", main->ray.pos_y);
			_3D(main, ray_count);
			// printf("cizdirdikten sonraki ray.distance[%f]\n", main->ray.distance);
			break;
		}
		main->ray.pos_x += main->ray.next_ray_step_x;
		main->ray.pos_y += main->ray.next_ray_step_y;
	}
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	main->ray.dir_x = ((cos(angle * ONE_DEGREE) > 0) * 2) - 1;
	main->ray.dir_y = ((sin(angle * ONE_DEGREE) > 0) * -2) + 1;
	main->ray.is_hit_x = false;
	main->ray.is_hit_y = false;
	// main->sprite.is_hit = false;
	main->sprite.is_sprite_ray_vertical = false;
	main->ray.distance_v = ray_vertical(main, angle,
		main->ray.dir_x, main->ray.dir_y); //dikey
	main->sprite.is_sprite_ray_horizontal = false;
	main->ray.distance_h = ray_horizontal(main, angle,
		main->ray.dir_x, main->ray.dir_y); //yatay
	if (main->ray.distance_v < main->ray.distance_h) //son çizim, duvar oluyor.
	{
		main->ray.distance = main->ray.distance_v;
		main->ray.hit_h = false;
		main->ray.hit_v = true;
		// main->sprite.oran = main->sprite.oran_v;
	}
	else
	{
		main->ray.distance = main->ray.distance_h;
		main->ray.hit_h = true;
		main->ray.hit_v = false;
		// main->sprite.oran = main->sprite.oran_h;
	} 
	if (main->sprite.dist_v < main->sprite.dist_h)// sprite için distance karşılaştırması.
	{
		// printf("vert\n");
		main->sprite.oran = main->sprite.oran_v;
	}
	else
	{
		// printf("horiz\n");
		main->sprite.oran = main->sprite.oran_h;
		// printf("oran_v:%f\n", main->sprite.oran);
	}
	main->ray.original_distance = main->ray.distance;//minimap's kacan isinlari icin
	main->ray.distance = main->ray.distance * cos((main->ply.rotation_angle - angle) * ONE_DEGREE);// balik gozunu engellemek icin.
	draw_ray(main, angle, ray_count);
}