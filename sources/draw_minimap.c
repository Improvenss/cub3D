/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 01:43:06 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 01:53:50 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap_test(t_main *main)
{
	int	x;
	int y;
	//printf("W_X:%d W_Y:%d RATE:%d\n", WINDOW_W , WINDOW_H, SCREEN_RATE);
	double M_Y = WINDOW_H / SCREEN_RATE;
	double M_X = WINDOW_W / SCREEN_RATE;
	//printf("M_X:%f M_Y:%f\n", M_X, M_Y);
	if ((M_Y / main->max_y) > (M_X / main->max_x))
		main->box_size = (M_X / main->max_x);
	else
		main->box_size = (M_Y / main->max_y);
	//printf("MAX_X:%d MAX_Y:%d\n", main->max_x, main->max_y);

	y = -1;
	while (++y <= main->max_y)
	{
		x = -1;
		while (++x <= main->max_x)
		{
			if (main->map[y][x] == '1')
				put_pixe(main->box_size * x, main->box_size * y, 0xffffff, &(main->mlx->img), main);
			else if (main->map[y][x] == '0')
				put_pixe(main->box_size * x, main->box_size * y, 0x000000, &(main->mlx->img), main);
			else
				put_pixe(main->box_size * x, main->box_size * y, 0x000000, &(main->mlx->img), main);
		}
	}
}

void	draw_player_test(t_main *main)
{
	int	x;
	int	y;
	int l;

	l = main->ply.thickness / 2;
	y = -1 * l;
	while (y <= l)
	{
		x = -1 * l;
		while (x <= l)
		{
			main->mlx->img.addr[(int)(WINDOW_W)
				* (int)(main->box_size * main->ply.y + y)
				+ (int)(main->box_size * main->ply.x + x)] = 0xff0000;
			x++;
		}
		y++;
	}
}

void	draw_player_directory(t_main *main)
{
	//double stick_x = cos(main->ply.rotationAngle * (PI / 180)) * 1;
	//double stick_y = sin(main->ply.rotationAngle * (PI / 180)) * -1;
	//main->mlx->img.addr[(int)(WINDOW_W) * (int)(main->box_size * (main->ply.y + stick_y)) + (int)(main->box_size * (main->ply.x + stick_x))] = 0xff0000;


	double ydy;
	double ydx;
	ydy = 1 * sin((main->ply.rotationAngle + 180) * (M_PI / 180));
	ydx = 1 * cos((main->ply.rotationAngle + 180) * (M_PI / 180));
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_value;
	
	ray_x = main->ply.x;
	ray_y = main->ply.y;
	dx = (main->ply.x - ydx) - main->ply.x;
	dy = (main->ply.y + ydy) - main->ply.y;

	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(ray_x, ray_y, main))
			main->mlx->img.addr[WINDOW_W * (int)floor(main->box_size * ray_y) + (int)floor(main->box_size * ray_x)] = 0x00ffff;
		else
			break;
		ray_x += dx / 2000;
		ray_y += dy / 2000;
	}
}

void	draw_ray(t_main *main, double angle)
{
	double ydy;
	double ydx;

	ydy = -1 * sin((angle - (FOV / 2)) * (M_PI / 180));
	ydx = -1 * cos((angle - (FOV / 2)) * (M_PI / 180));

	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_value;
	
	ray_x = main->ply.x;
	ray_y = main->ply.y;
	dx = (main->ply.x - ydx) - main->ply.x;
	dy = (main->ply.y + ydy) - main->ply.y;

	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(ray_x, ray_y, main))
			main->mlx->img.addr[WINDOW_W * (int)floor(main->box_size * ray_y)
				+ (int)floor(main->box_size * ray_x)] = 0xFF0000;
		else
			break;
		ray_x += dx / 2000;
		ray_y += dy / 2000;
	}
	// printf("x:%f y:%f\n", ray_x, ray_y);
}

void	draw_minimap(t_main *main)
{
	draw_minimap_test(main);
	draw_player_test(main);

	double angle;
	double maxangle;

	angle = main->ply.rotationAngle;
	maxangle = angle + (FOV / 2.0);// +30º
	// printf("maxangle[%fº]\n", maxangle);
	while (angle <= maxangle)
	{
		// draw_ray_ikinci_deneme(main, angle);// right side 30º
		// draw_ray_ikinci_deneme(main, angle + (FOV / 2.0));// left side 30º
		draw_ray(main, angle);// right side 30º
		draw_ray(main, angle + (FOV / 2.0));// left side 30º
		angle += (FOV / 2.0) / ((FOV_THICKNESS) / 2.0);// angle += 30 / 60; -> 0.5;
	}
	draw_player_directory(main);
}