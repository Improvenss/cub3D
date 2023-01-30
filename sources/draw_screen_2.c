/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 00:13:54 by gsever            #+#    #+#             */
/*   Updated: 2023/01/31 00:14:49 by gsever           ###   ########.fr       */
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
	int	floor;

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
void	three_dimension(t_main *main, int ray_count)
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
		&& main->sprite.is_hit == true)
	{
		if (main->is_hit_val == 'Z')
			draw_xpm_to_sprite(main, loc,
				main->xpm[main->xpm_number_sprite], &main->draw);
		else if (main->is_hit_val == 'M')
			draw_xpm_to_sprite(main, loc,
				main->xpm[main->xpm_number_sprite_m], &main->draw);
	}
}
