/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/29 22:09:04 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_xpm_to_sprite(t_main *main, int location, t_xpm xpm)
{
	int i = -1;
	int find_pixel = 0;
	if (main->sprite.value >= 0 && main->sprite.value <= 1.0)
		find_pixel = (main->sprite.value) * (xpm.width); // resmin hangi sütununu çizeceğini belirtiyor.
	int img_loc = (xpm.width * (xpm.height / 2)) + find_pixel;
	int oran = (int)((double)((xpm.height / 2) * BOX_SIZE) / main->sprite.distance); // resmin sürekli bize bakması için dist sprite boyunca aynı değere sahip olmalı.
	if (oran > 4000)
		oran = 4000;
	int color;
	while (++i < oran)
	{
		color = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
		if ((location - (WINDOW_W * i)) >= 0 && main->sprite.value > 0 && color >= 0) //yukarı
			main->screen.addr[(location - (WINDOW_W * i))] = color;
		color = xpm.img.addr[img_loc + xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i)) && main->sprite.value > 0 && color >= 0) // aşağı
			main->screen.addr[(location + (WINDOW_W * i))] = color;
	}
}

void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
{
	int	i = -1;
	int find_pixel = 0;
	if (main->ray.hit_h == true)
		find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	else if (main->ray.hit_v == true)
		find_pixel = ((main->ray.pos_y - floor(main->ray.pos_y)) * xpm.width); // resimdeki pixel sütun konumunu bulur.
	int img_loc = (xpm.width * (xpm.height / 2)) + find_pixel;
	int color;
	while (++i < oran)
	{
		color = xpm.img.addr[img_loc - xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];//xpm.img.addr[img_loc - (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
		if ((location - (WINDOW_W * i)) >= 0 && color >= 0) //yukarı
			main->screen.addr[(location - (WINDOW_W * i))] = color;
		color = xpm.img.addr[img_loc + xpm.width * (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];//xpm.img.addr[img_loc + (xpm.width * ((i / (WINDOW_H / main->xpm[0].height)) % xpm.height))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i)) && color >= 0) // aşağı
			main->screen.addr[(location + (WINDOW_W * i))] = color;
	}
}
