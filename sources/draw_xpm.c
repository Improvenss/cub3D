/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 23:56:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	put_xpm_to_sprite(t_main *main, int location, t_xpm xpm)
// {
	// mlx_put_image_to_window(main->mlx.ptr, main->mlx.win, xpm.img.ptr, location, main->key.screen_mid);
// }

// void	draw_xpm_to_sprite(t_main *main, int location, int oran, t_xpm xpm)
// {
// 	int	
// }

// void	draw_xpm_to_sprite(t_main *main, int location, int oran, t_xpm xpm) // sütun bilgisi var lakin genişlik bilgisi yok.
// {
// 	int i = -1;
// 	static int l = 0;
// 	int find_pixel = ((main->sprite.s_y - floor(main->sprite.s_y)) * (xpm.width)); // resmin hangi sütununu çizeceğini belirtiyor.
// 	int img_loc = (xpm.width * (xpm.height / 2)) + find_pixel - l;
// 	l++;
// 	if (l > xpm.width)
// 		l = 0;
// 	oran = (int)((double)((xpm.height / 2) * BOX_SIZE) / main->sprite.distance); // resmin sürekli bize bakması için dist sprite boyunca aynı değere sahip olmalı.
// 	while (++i < oran / 2)
// 	{
// 		if ((location - (WINDOW_W * i)) >= 0) //yukarı
// 			main->screen.addr[(location - (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
// 		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))) // aşağı
// 			main->screen.addr[(location + (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
// 	}
// }

void	draw_xpm_to_sprite(t_main *main, int location, int oran, t_xpm xpm)
{
	(void)main;
	(void)xpm;
	(void)oran;
	int i = -1;

	int find_pixel = 0;
	if (main->ray.hit_h == true)
		find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	else if (main->ray.hit_v == true)
		find_pixel = ((main->ray.pos_y - floor(main->ray.pos_y)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	int img_loc = (xpm.width * (xpm.height / 2)) + find_pixel;
	while (++i < oran)
	{
		if ((location - (WINDOW_W * i)) >= 0) //yukarı
			main->screen.addr[(location - (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
			// main->screen.addr[(location - (WINDOW_W * i))] = xpm.img.addr[(location - (WINDOW_W * i))];
		// if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))) // aşağı
			// main->screen.addr[(location + (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
			// main->screen.addr[(location + (WINDOW_W * i))] = xpm.img.addr[(location - (WINDOW_W * i))];
	}
}

void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
{
	int	i = -1;
	int find_pixel = 0;
	if (main->ray.hit_h == true)// && main->ray.dir_y == -1)
		find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	else if (main->ray.hit_v == true)
		find_pixel = ((main->ray.pos_y - floor(main->ray.pos_y)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	int img_loc = (xpm.width * xpm.height / 2) + find_pixel;
	while (++i < oran)
	{
		if ((location - (WINDOW_W * i)) >= 0) //yukarı
			main->screen.addr[(location - (WINDOW_W * i))] = xpm.img.addr[img_loc - xpm.width * (int)((double)i * (double)xpm.width / (double)(oran * 2))];//xpm.img.addr[img_loc - (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))) // aşağı
			main->screen.addr[(location + (WINDOW_W * i))] = xpm.img.addr[img_loc + xpm.width * (int)((double)i * (double)xpm.width / (double)(oran * 2))];//xpm.img.addr[img_loc + (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
	}
}

// /**
//  * @brief 
//  * 
//  * Gerekli argler:
//  * 	 Hangi duvara carptiginin bilinmesi gerekiyor;
//  * 		dir_x, dir_y, hit_v, hit_h, hit_x, hit_y
//  * bpp: 32, line_size: 256, endian: 0
//  * @param main 
//  * @param location 
//  * @param color 
//  */
// void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
// {
// 	int	i = -1;
// 	if (main->ray.hit_h == true && main->ray.dir_y == -1)
// 	{
// 		int	find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x)) * xpm.width);
// 		i = -1;
// 		while (++i <= oran && (WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i)) && (location + (WINDOW_W * i)) >= 0)
// 		{
// 			main->screen.addr[location + (WINDOW_W * i)] = xpm.img.addr[find_pixel + (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
// 		}
// 	}
// 	// else
// 	// {
// 	// 	(void)xpm;
// 	// 	while (++i <= oran && i <= WINDOW_H)
// 	// 		main->screen.addr[location + (WINDOW_W * i)] = 0xffffff;
// 	// }
// }