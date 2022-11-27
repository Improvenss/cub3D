/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:54:52 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 03:05:13 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	draw_ray_walls(t_main *main)
// {
	
// }

/**
 * @brief Putting pixels to the bottom side main->img.
 * 
 * @param main 
 */
void	draw_floor(t_main *main, int x, int y)
{
	x = -1;
	while (++x < WINDOW_W)
	{
		y = (WINDOW_H / 2) - 1;
		while (++y < WINDOW_H)
		{
			main->mlx->img.addr[WINDOW_W * y + x] = COLOR_GREEN;
		}
	}
}

/**
 * @brief Putting pixels to the top side main->img.
 * 
 * @param main 
 */
void	draw_ceil(t_main *main, int x, int y)
{
	x = -1;
	while (++x < WINDOW_W)
	{
		y = -1;
		while (++y < WINDOW_H / 2)
		{
			main->mlx->img.addr[WINDOW_W * y + x] = COLOR_LBLUE;
		}
	}
}

int	draw_render(t_main *main)
{
	draw_ceil(main, -1, -1);
	draw_floor(main, -1, -1);
	// draw_ray_walls(main);
	return (0);
}