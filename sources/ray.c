/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 22:10:56 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 11:25:26 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	ray_vertical_step_loop(t_main *main, double angle,
	double dir_x, double dir_y)
{
	while (main->ply.pos_x + main->ray.dx * dir_x - 0.0001 >= 0
		&& main->ply.pos_x + main->ray.dx * dir_x - 0.0001 <= main->map.max_x
		&& main->ply.pos_y + main->ray.dy * dir_y >= 0
		&& main->ply.pos_y + main->ray.dy * dir_y <= main->map.max_y)
	{
		main->ray.dx += 0.0001;
		if (is_wall_v2(main, main->ply.pos_x + main->ray.dx * dir_x,
				main->ply.pos_y + main->ray.dy * dir_y, angle))
		{
			main->ray.is_hit_vertical = true;
			main->ray.loc_x = main->ray.dx * dir_x;
			main->ray.loc_y = main->ray.dy * dir_y;
			main->ray.distance_v = sqrt((main->ray.loc_x * main->ray.loc_x)
					+ (main->ray.loc_y * main->ray.loc_y));
			return (true);
		}
		main->ray.dx += 1.0 - 0.0001;
		main->ray.dy = fabs(tan(angle * ONE_DEGREE) * main->ray.dx);
	}
	return (false);
}

void	ray_vertical(t_main *main, double angle, double dir_x, double dir_y)
{
	if (dir_x == -1)
		main->ray.dx = main->ply.pos_x - floor(main->ply.pos_x);
	else
		main->ray.dx = ceil(main->ply.pos_x) - main->ply.pos_x;
	main->ray.dy = fabs(tan(angle * ONE_DEGREE) * main->ray.dx);
	main->ray.loc_x = main->ray.dx * dir_x;
	main->ray.loc_y = main->ray.dy * dir_y;
	if (ray_vertical_step_loop(main, angle, dir_x, dir_y) == false)
		main->ray.distance_v = 10000;
}

static bool	ray_horizontal_step_loop(t_main *main, double angle,
	double dir_x, double dir_y)
{
	while (main->ply.pos_x + main->ray.dx * dir_x >= 0
		&& main->ply.pos_x + main->ray.dx * dir_x <= main->map.max_x
		&& main->ply.pos_y + main->ray.dy * dir_y - 0.0001 >= 0
		&& main->ply.pos_y + main->ray.dy * dir_y - 0.0001 <= main->map.max_y)
	{
		main->ray.dy += 0.001;
		if (is_wall_v2(main, main->ply.pos_x + main->ray.dx * dir_x,
				main->ply.pos_y + main->ray.dy * dir_y, angle))
		{
			main->ray.is_hit_horizontal = true;
			main->ray.loc_x = main->ray.dx * dir_x;
			main->ray.loc_y = main->ray.dy * dir_y;
			main->ray.distance_h = sqrt((main->ray.loc_x * main->ray.loc_x)
					+ (main->ray.loc_y * main->ray.loc_y));
			return (true);
		}
		main->ray.dy += 1.0 - 0.001;
		main->ray.dx = fabs(main->ray.dy / tan(angle * ONE_DEGREE));
	}
	return (false);
}

void	ray_horizontal(t_main *main, double angle, double dir_x, double dir_y)
{
	if (dir_y == -1)
		main->ray.dy = main->ply.pos_y - floor(main->ply.pos_y);
	else
		main->ray.dy = ceil(main->ply.pos_y) - main->ply.pos_y;
	main->ray.dx = fabs(main->ray.dy / tan(angle * ONE_DEGREE));
	main->ray.loc_y = main->ray.dy * dir_y;
	main->ray.loc_x = main->ray.dx * dir_x;
	if (ray_horizontal_step_loop(main, angle, dir_x, dir_y) == false)
		main->ray.distance_h = 10000;
}
