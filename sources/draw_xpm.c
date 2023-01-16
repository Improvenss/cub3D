/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/16 18:05:13 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * 
 * Gerekli argler:
 * 	 Hangi duvara carptiginin bilinmesi gerekiyor;
 * 		dir_x, dir_y, hit_v, hit_h, hit_x, hit_y
 * bpp: 32, line_size: 256, endian: 0
 * @param main 
 * @param location 
 * @param color 
 */
void	draw_xpm_to_wall(t_main *main, int location, int oran, t_xpm xpm)
{
	// int	color;
	int	i = -1;
	if (main->ray.hit_h == true && main->ray.dir_y == -1)
	{
		int	screen_oran = (main->ray.hit_x - floor(main->ray.hit_x)) * 100; //A
		int	img_oran = (screen_oran * xpm.img.bpp); //L


	i = -1;

	// printf("bpp: %d, line_size: %d, endian: %d\n", xpm.img.bpp, xpm.img.line_size, xpm.img.endian);
	printf("screen_orn %d, img_oran %d\n", screen_oran, img_oran);
	while (++i <= oran)
	{
		main->screen.addr[location + (WINDOW_W * i)] = xpm.img.addr[img_oran + (xpm.img.bpp * i)];
	}
	// main->screen.addr[location] = color;//ust taraf
	}
	else
	{
		while (++i <= oran)
			main->screen.addr[location + (WINDOW_W * i)] = xpm.img.addr[i];
	}
}