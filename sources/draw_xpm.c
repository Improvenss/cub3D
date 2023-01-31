/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/31 12:15:13 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_xpm_to_sprite(t_main *main, int location,
	t_xpm xpm, t_draw *draw)
{
	int	i;

	if (main->sprite.value >= 0 && main->sprite.value <= 1.0)
		draw->find_pixel = (main->sprite.value) * (xpm.width);
	draw->img_loc = (xpm.width * (xpm.height / 2))
		+ draw->find_pixel;
	draw->oran = (int)((double)((xpm.height / 2) * BOX_SIZE)
			/ main->sprite.distance);
	if (draw->oran > 4000)
		draw->oran = 4000;
	i = -1;
	while (++i < draw->oran)
	{
		draw->color = xpm.img.addr[draw->img_loc - xpm.width
			* (int)((double)i
				* ((double)xpm.width / (double)(draw->oran * 2)))];
		if ((location - (WINDOW_W * i)) >= 0
			&& main->sprite.value > 0 && draw->color >= 0)
			main->screen.addr[(location - (WINDOW_W * i))] = draw->color;
		draw->color = xpm.img.addr[draw->img_loc + xpm.width * (int)((double)i
				* ((double)xpm.width / (double)(draw->oran * 2)))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))
			&& main->sprite.value > 0 && draw->color >= 0)
			main->screen.addr[(location + (WINDOW_W * i))] = draw->color;
	}
}

void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
{
	int	i;

	if (main->ray.hit_h == true)
		main->draw.find_pixel = ((main->ray.pos_x - floor(main->ray.pos_x))
				* xpm.width);
	else if (main->ray.hit_v == true)
		main->draw.find_pixel = ((main->ray.pos_y - floor(main->ray.pos_y))
				* xpm.width);
	main->draw.img_loc = (xpm.width * (xpm.height / 2))
		+ main->draw.find_pixel;
	i = -1;
	while (++i < oran)
	{
		main->draw.color = xpm.img.addr[main->draw.img_loc - xpm.width
			* (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
		if ((location - (WINDOW_W * i)) >= 0 && main->draw.color >= 0)
			main->screen.addr[(location - (WINDOW_W * i))] = main->draw.color;
		main->draw.color = xpm.img.addr[main->draw.img_loc + xpm.width
			* (int)((double)i * ((double)xpm.width / (double)(oran * 2)))];
		if ((WINDOW_H * WINDOW_W) >= (location + (WINDOW_W * i))
			&& main->draw.color >= 0)
			main->screen.addr[(location + (WINDOW_W * i))] = main->draw.color;
	}
}
