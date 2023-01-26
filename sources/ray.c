/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:10:56 by gsever            #+#    #+#             */
/*   Updated: 2023/01/26 23:59:35 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	ray_vertical(t_main *main, double angle, double dir_x, double dir_y)
{
	double vdy;
	double vdx;

	if (dir_x == -1)
		vdx = main->ply.pos_x - floor(main->ply.pos_x);
	else
		vdx = ceil(main->ply.pos_x) - main->ply.pos_x;
	vdy = fabs(tan(angle * ONE_DEGREE) * vdx);

	double loc_x = vdx*dir_x;
	double loc_y = vdy*dir_y;
	// printf("Box:Vx: %f Vy:%f\n", loc_x, loc_y);
	while (main->ply.pos_x + vdx*dir_x - 0.0001 >= 0
		&& main->ply.pos_x + vdx*dir_x - 0.0001 <= main->map.max_x
		&& main->ply.pos_y + vdy*dir_y >= 0
		&& main->ply.pos_y + vdy*dir_y <= main->map.max_y)
	{
		vdx += 0.0001;
		if (is_wall_v2(main, main->ply.pos_x + vdx*dir_x, main->ply.pos_y + vdy*dir_y, VERTICAL, dir_x, dir_y, angle))
		{
			main->ray.is_hit_vertical = true;
			// printf("V:ture\n");
			loc_x = vdx*dir_x;
			loc_y = vdy*dir_y;
			// printf("Vx: %f Vy:%f\n", loc_x, loc_y);
			// printf("Px: %f Py:%f\n", main->ply.pos_x, main->ply.pos_y);
			break;
		}
		vdx += 1 - 0.0001;
		vdy = fabs(tan(angle * ONE_DEGREE) * vdx);
	}
	double distance;
	if (main->ray.is_hit_vertical == true)
		distance = sqrt((loc_x*loc_x) + (loc_y*loc_y));
	else
		distance = 10000;
	return (distance);
}

double	ray_horizontal(t_main *main, double angle, double dir_x, double dir_y)
{
	double hdy;
	double hdx;

	if (dir_y == -1)
		hdy = main->ply.pos_y - floor(main->ply.pos_y);
	else
		hdy = ceil(main->ply.pos_y) - main->ply.pos_y;
	hdx = fabs(hdy / tan(angle * ONE_DEGREE));

	double loc_y = hdy*dir_y;
	double loc_x = hdx*dir_x;
	// printf("loc_x:%f, hdx:%f, dir_x:%f\n", loc_x, hdx, dir_x);
// printf("Box:Hx: %f Hy:%f\n", loc_x, loc_y);
	while (main->ply.pos_x + hdx*dir_x >= 0
		&& main->ply.pos_x + hdx*dir_x <= main->map.max_x
		&& main->ply.pos_y + hdy*dir_y - 0.0001 >= 0
		&& main->ply.pos_y + hdy*dir_y - 0.0001 <= main->map.max_y)
	{
		hdy += 0.001;
		if (is_wall_v2(main, main->ply.pos_x + hdx*dir_x, main->ply.pos_y + hdy*dir_y, HORIZONTAL, dir_x, dir_y, angle))
		{
			main->ray.is_hit_horizontal = true;
		// printf("H:ture\n");
			loc_x = hdx*dir_x;
			loc_y = hdy*dir_y;
		// printf("Hx: %f Hy:%f\n", loc_x, loc_y);
		// printf("Px: %f Py:%f\n", main->ply.pos_x, main->ply.pos_y);
			break;
		}
		hdy += 1 - 0.001;
		hdx = fabs(hdy / tan(angle * ONE_DEGREE));
	}
	// printf("loc_x:%f, loc_y:%f\n", loc_x, loc_y);
	double distance;
	if (main->ray.is_hit_horizontal == true)
		distance = sqrt((loc_x*loc_x) + (loc_y*loc_y));
	else
		distance = 10000;
	// printf("ray_horizontal -> distance: %f\n", distance);
	return (distance);
}

