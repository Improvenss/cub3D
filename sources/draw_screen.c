/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:01:57 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 21:13:06 by gsever           ###   ########.fr       */
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
			main->screen.addr[WINDOW_W * y + x] = ceil;
			x++;
		}
		y++;
	}
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
		{
			main->screen.addr[WINDOW_W * y + x] = floor;
			x++;
		}
		y++;
	}
}

void _3D(t_main *main, int ray_count)
{
	int loc;
	int oran;
	main->ray.distance = main->ray.distance * (double)BOX_SIZE * ((double)WINDOW_H / (double)WINDOW_W);
	loc = (WINDOW_W * main->key.screen_mid) - ray_count;// 180000. pixel
	oran = (((double)WINDOW_H / 2.0) / main->ray.distance) * (double)BOX_SIZE;
	if (oran > 4000)// duvarimizin uzakligimiza gore bastirilan yuksekligini belirtiyor. Cok yaklastigimiz icin bu deger 40.000 flaan oluyor hesaplarken programda kasma meydana geliyor. O yuzden 4000'de sinirlandirdim, duvara cok yaklastigimizda cok genis gozukuyor ama o kadar olacak.
		oran = 4000;
	// printf("oran: %d\n", oran);
	if (main->ray.hit_h == true && main->ray.dir_y == -1)// kuzey
		draw_xpm_to_wall(main, loc, oran, main->xpm[0]);
	else if (main->ray.hit_h == true && main->ray.dir_y == 1)// guney
		draw_xpm_to_wall(main, loc, oran, main->xpm[1]);
	else if (main->ray.hit_v == true && main->ray.dir_x == 1)// dogu
		draw_xpm_to_wall(main, loc, oran, main->xpm[2]);
	else if (main->ray.hit_v == true && main->ray.dir_x == -1)// bati
		draw_xpm_to_wall(main, loc, oran, main->xpm[3]);
	
	// if (main->ray.original_distance > main->sprite.distance)
	// {
		if (main->sprite.is_hit == true)
		{
			// printf("s_dist:%f\n", main->sprite.distance);
			// printf("w_dist:%f\n", main->ray.distance);
			// draw_xpm_to_sprite(main, loc, oran, main->xpm[5]);
			// put_xpm_to_sprite(main, loc, main->xpm[4]);
		}
	// }
	// if (main->ray.is_door == true)
		// draw_xpm_to_wall(main, loc, oran, main->xpm[4]);
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
	while (1)
	{
		if (!is_wall(main, main->ray.pos_x, main->ray.pos_y)
			&& (sqrt(((main->ply.pos_x - main->ray.pos_x) * (main->ply.pos_x - main->ray.pos_x)) + ((main->ply.pos_y - main->ray.pos_y) * (main->ply.pos_y - main->ray.pos_y))) <= main->ray.original_distance))
			main->mini_map.addr[(BOX_SIZE * (main->map.max_x + 1))
				* (int)floor(BOX_SIZE * main->ray.pos_y)
				+ (int)floor(BOX_SIZE * main->ray.pos_x)] = COLOR_GREEN;// player's minimap rays.
		else
		{
			if ((int)floor(main->ply.rotation_angle) == (int)floor(angle))
			{
				// printf("rotation: %f, angle: %f\n\n", main->ply.rotation_angle, angle);
				// printf("rotation: %d, angle: %d\n", (int)floor(main->ply.rotation_angle), (int)floor(angle));
				check_door_open_or_close(main, main->ray.pos_x, main->ray.pos_y);
			}
			main->ray.pos_x -= main->ray.hit_x / (WINDOW_H / 2);
			main->ray.pos_y -= main->ray.hit_y / (WINDOW_H / 2);
			// printf("pos_x: %f\n", main->ray.pos_x);
			// printf("pos_y: %f\n", main->ray.pos_y);
			_3D(main, ray_count);
			break;
		}
		main->ray.pos_x += main->ray.hit_x / (WINDOW_H / 2);
		main->ray.pos_y += main->ray.hit_y / (WINDOW_H / 2);
	}
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	main->ray.dir_x = ((cos(angle * ONE_DEGREE) > 0) * 2) - 1;
	main->ray.dir_y = ((sin(angle * ONE_DEGREE) > 0) * -2) + 1;
	main->ray.is_hit_x = false;
	main->ray.is_hit_y = false;
	main->ray.distance_v = ray_vertical(main, angle,
		main->ray.dir_x, main->ray.dir_y); //dikey
	main->ray.distance_h = ray_horizontal(main, angle,
		main->ray.dir_x, main->ray.dir_y); //yatay
	// printf("V: %f H:%f\n", distance_v, distance_h);
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
	main->ray.original_distance = main->ray.distance;//minimap's kacan isinlari icin
	main->ray.distance = main->ray.distance * cos((main->ply.rotation_angle - angle) * ONE_DEGREE);// balik gozunu engellemek icin.
	draw_ray(main, angle, ray_count);
}