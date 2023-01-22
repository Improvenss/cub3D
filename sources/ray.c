/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:10:56 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 17:54:56 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	ray_vertical(t_main *main, double angle, double dir_x, double dir_y)
{
	double	vdy;
	double	vdx;
	double	tmp_x;
	double	tmp_y;
	double	distance;

	if (dir_x == -1)
		vdx = main->ply.pos_x - floor(main->ply.pos_x);
	else
		vdx = ceil(main->ply.pos_x) - main->ply.pos_x;
	vdy = fabs(tan(angle * ONE_DEGREE) * vdx);
	tmp_x = vdx * dir_x;
	tmp_y = vdy * dir_y;
	while (main->ply.pos_x + vdx * dir_x - 0.0001 >= 0
		&& main->ply.pos_x + vdx * dir_x - 0.0001 <= main->map.max_x
		&& main->ply.pos_y + vdy * dir_y >= 0
		&& main->ply.pos_y + vdy * dir_y <= main->map.max_y)
	{
		vdx = vdx + 0.001;
		if (is_wall_v2(main, main->ply.pos_x + vdx * dir_x,
				main->ply.pos_y + vdy * dir_y))
		{
			main->ray.is_hit_y = true;
			tmp_x = vdx * dir_x;
			tmp_y = vdy * dir_y;
			break ;
		}
		vdx = vdx + 1 - 0.001;
		vdy = fabs(tan(angle * ONE_DEGREE) * vdx);
	}
	if (main->ray.is_hit_y == true)
		distance = sqrt((tmp_x * tmp_x) + (tmp_y * tmp_y));
	else
		distance = 10000;
	return (distance);
}

double	ray_horizontal(t_main *main, double angle, double dir_x, double dir_y)
{
	double	hdy;
	double	hdx;
	double	tmp_x;
	double	tmp_y;
	double	distance;

	if (dir_y == -1)
		hdy = main->ply.pos_y - floor(main->ply.pos_y);
	else
		hdy = ceil(main->ply.pos_y) - main->ply.pos_y;
	hdx = fabs(hdy / tan(angle * ONE_DEGREE));
	tmp_x = hdx * dir_x;
	tmp_y = hdy * dir_y;
	if (!is_wall(main, main->ply.pos_x + hdx * dir_x,
			main->ply.pos_y + hdy * dir_y))
	{
		while (main->ply.pos_x + hdx * dir_x >= 0
			&& main->ply.pos_x + hdx * dir_x <= main->map.max_x
			&& main->ply.pos_y + hdy * dir_y - 0.0001 >= 0
			&& main->ply.pos_y + hdy * dir_y - 0.0001 <= main->map.max_y)
		{
			hdy = hdy + 0.001;
			if (is_wall_v2(main, main->ply.pos_x + hdx * dir_x,
					main->ply.pos_y + hdy * dir_y))
			{
				main->ray.is_hit_x = true;
				tmp_x = hdx * dir_x;
				tmp_y = hdy * dir_y;
				break ;
			}
			hdy = hdy + 1 - 0.001;
			hdx = fabs(hdy / tan(angle * ONE_DEGREE));
		}
	}
	else
		main->ray.is_hit_x = true;
	if (main->ray.is_hit_x == true)
		distance = sqrt((tmp_x * tmp_x) + (tmp_y * tmp_y));
	else
		distance = 10000;
	return (distance);
}
