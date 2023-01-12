/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:55:29 by akaraca           #+#    #+#             */
/*   Updated: 2022/12/07 19:55:29 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall(double x, double y, t_main *main)
{
	int xX;
	int yY;

	if (x < 0 || x > main->max_x || y < 0 || y > main->max_y)
		return (1);
	xX = floor(x);
	yY = floor(y);
	if (main->map[yY][xX] != '1')
		return (0);
	return (1);
}

void put_pixel(double x, int y, double color, t_img *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < BOX_SIZE)
	{
		if (color == -123.0)
			break ;
		j = -1;
		while (++j < BOX_SIZE)
		{
			img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = color;
			if (j == BOX_SIZE - 1)
				img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = COLOR_TUNDORA;
		}
		if (i == BOX_SIZE - 1)
		{
			j = -1;
			while (++j < BOX_SIZE)
				img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = COLOR_TUNDORA;
		}
	}
}

void	draw_mini_map_test(t_main *main)
{
	int	x;
	int y;
	// int color = 255*(main->texture.rgb_c[0] * 65536) + (main->texture.rgb_c[1] * 256) + main->texture.rgb_c[2];

	y = -1;
	while (++y <= main->max_y)
	{
		x = -1;
		while (++x <= main->max_x)
		{
			if (main->map[y][x] == '1')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0xffffff, &(main->mini_map));
			else if (main->map[y][x] == '0')
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, 0x000000, &(main->mini_map));
			else
				put_pixel(BOX_SIZE * x, BOX_SIZE * y, -123.0, &(main->mini_map));
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
			main->mini_map.addr[(int)(WINDOW_W) * (int)(BOX_SIZE * main->ply.y + y) + (int)(BOX_SIZE * main->ply.x + x)] = 0xff0000;
			x++;
		}
		y++;
	}
}

void	draw_player_directory(t_main *main)
{
	double ydy;
	double ydx;
	ydy = 1 * sin((main->ply.rotation_angle + 180) * (M_PI / 180));
	ydx = 1 * cos((main->ply.rotation_angle + 180) * (M_PI / 180));
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
			main->mini_map.addr[WINDOW_W * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = COLOR_ORANGE;
		else
			break;
		ray_x += dx / 2000;
		ray_y += dy / 2000;
	}
	//printf("x:%f y:%f\n", ray_x, ray_y);
}


// void ray(t_main *main, double angle)
// {
// 	double ydy;
// 	double ydx;
// 	ydy = sin((angle + 180) * (M_PI / 180));
// 	ydx = cos((angle + 180) * (M_PI / 180));
// 	double	ray_x;
// 	double	ray_y;
// 	double	dx;
// 	double	dy;
// 	double	max_value;
	
// 	ray_x = main->ply.x;
// 	ray_y = main->ply.y;
// 	dx = (main->ply.x - ydx) - main->ply.x;
// 	dy = (main->ply.y + ydy) - main->ply.y;

// 	max_value = fmax(fabs(dx), fabs(dy));
// 	dx /= max_value;
// 	dy /= max_value;
// 	while (1)
// 	{
// 		if (!is_wall(ray_x, ray_y, main))
// 			main->img.addr[WINDOW_W * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = 0x00ff00;
// 		else
// 			break;
// 		ray_x += dx / 2000;
// 		ray_y += dy / 2000;
// 	}
// }

void	draw_walls(t_main *main, double distance, int ray_count)
{
	(void)main;
	int		location;
	int		mid;
	double	oran;
	int		i;
	int		color;

	distance *= (double)BOX_SIZE;
	mid = WINDOW_H / 2;
	location = (WINDOW_W * mid) - ray_count;
	oran = (double)WINDOW_H / distance;
	if (distance > 3)
		color = 0x00ff00 * distance;
	else
		color = 0xff00ff;
	i = 0;
	while (i < oran)
	{
		main->screen.addr[(location + (WINDOW_W * i))] = color;
		main->screen.addr[(location - (WINDOW_W * i))] = color;
		i++;
	}
}

// void ben_3_boyut_umut(t_main *main, double distance, int ray_count)//**************************************************************************
// {
// 	// (void)main;
// 	int loc;
// 	int mid;
// 	double oran;
// 	int	i;
// 	int color;

// 	distance = distance * (double)BOX_SIZE;
// 	i = 0;
// 	mid = WINDOW_H / 2;
// 	loc = (WINDOW_W * mid) - ray_count;
// 	// if (ray_count == 0)
// 		// printf("[%d]: %f\n", ray_count, distance);
// 	oran = (double)WINDOW_H / distance;
// 	if (distance > 3)
// 		color = 0x00ff00 * distance;
// 	else
// 		color = 0xff00ff;
// 	while (i < oran)
// 	{
// 		main->screen.addr[(loc + (WINDOW_W * i))] = color;
// 		main->screen.addr[(loc - (WINDOW_W * i))] = color;
// 		i++;
// 	}
// }

double	ray_vertical(t_main *main, double angle, int dir_x, int dir_y)
{
	double vdy;
	double vdx;

	if (dir_x == -1)
		vdx = main->ply.x - floor(main->ply.x);
	else
		vdx = ceil(main->ply.x) - main->ply.x;
	vdy = fabs(tan(angle * (M_PI / 180)) * vdx);

	double tmp_x = vdx*dir_x;
	double tmp_y = vdy*dir_y;

	if (!is_wall(main->ply.x + vdx*dir_x, main->ply.y + vdy*dir_y, main))
	{
		while (1)
		{
			vdx = vdx + 1;
			vdy = fabs(tan(angle * (M_PI / 180)) * vdx);
			if (!is_wall(main->ply.x + vdx*dir_x, main->ply.y + vdy*dir_y, main))
			{
				tmp_x = vdx*dir_x;
				tmp_y = vdy*dir_y;
			}
			else
				break ;
		}
	}
	double distance;
	distance = sqrt((tmp_x*tmp_x) + (tmp_y*tmp_y));
	//printf("vertical_distance:%f\n", distance);
	//printf("tmp_x:%f, tmp_y:%f\n", tmp_x, tmp_y);
	return (distance);
}

double ray_horizonal(t_main *main, double angle, int dir_x, int dir_y)
{
	double hdy;
	double hdx;

	if (dir_y == -1)
		hdy = floor(main->ply.y) - main->ply.y;
	else
		hdy = ceil(main->ply.y) - main->ply.y;
	hdx = fabs(hdy / tan(angle * (M_PI / 180)));

	double tmp_y = hdy*dir_y;
	double tmp_x = hdx*dir_x;

	if (!is_wall(main->ply.x + hdx*dir_x, main->ply.y + hdy*dir_y, main))
	{
		while (1)
		{
			hdy = hdy + 1;
			hdx = fabs(hdy / tan(angle * (M_PI / 180)));
			if (!is_wall(main->ply.x + hdx*dir_x, main->ply.y + hdy*dir_y, main))
			{
				tmp_y = hdy*dir_y;
				tmp_x = hdx*dir_x;
			}
			else
				break;
		}
	}
	double distance;
	distance = sqrt((tmp_x*tmp_x) + (tmp_y*tmp_y));
	// printf("horizonal_distance:%f\n", distance);
	// printf("tmp_x:%f, tmp_y:%f\n", tmp_x, tmp_y);
	return (distance);
}

void draw_ray(double distance, int dir_x, int dir_y, t_main *main, double angle, int ray_count)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	
	ray_x = main->ply.x;
	ray_y = main->ply.y;
	dx = distance * fabs(cos(angle * (M_PI / 180))) * dir_x;
	dy = distance * fabs(sin(angle * (M_PI / 180))) * dir_y;
	dx /= distance;
	dy /= distance;
	while (1)
	{
		if (!is_wall(ray_x, ray_y, main))
		{
			if (angle == main->ply.rotation_angle)
				main->mini_map.addr[WINDOW_W * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = COLOR_ORANGE;
			else
				main->mini_map.addr[WINDOW_W * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = COLOR_GREEN;
		}
		else
		{
			draw_walls(main, distance, ray_count);
			break;
		}
		ray_x += dx / 2000;
		ray_y += dy / 2000;
	}
//  while (1)
    // {
    //     if (!is_wall(ray_x, ray_y, main))
    //         main->mini_map.addr[(BOX_SIZE * (main->max_x +1)) * (int)floor(BOX_SIZE * ray_y) + (int)floor(BOX_SIZE * ray_x)] = 0x00ff00;
	// 	else
	// 	{
	// 		//ben_3_boyut_umut_2(main, (main->ply.x + ray_x*dir_x), (main->ply.y + ray_y*dir_y), ray_count);
	// 		ben_3_boyut_umut(main, distance, ray_count);
	// 		break;
	// 	}
    //     ray_x += dx / 2000;
    //     ray_y += dy / 2000;
    // }
}

void	raycasting(t_main *main, double angle, int ray_count)
{
	int dir_x = ((cos(angle * (M_PI / 180)) > 0) * 2) - 1;
	int dir_y = ((sin(angle * (M_PI / 180)) > 0) * -2) + 1;
	double distance_v;
	double distance_h;
	double distance;
	distance_v = ray_vertical(main, angle, dir_x, dir_y); //dikey
	distance_h = ray_horizonal(main, angle, dir_x, dir_y); //yatay
	if (distance_v < distance_h)
		distance = distance_v;
	else
		distance = distance_h;
	draw_ray(distance, dir_x, dir_y, main, angle, ray_count);
}

int	ft_loop(t_main *main)
{
	double	angle;
	// long i = 10000000;
	// while (i > 0)
	// 	i--;
	key_function(main);
	draw_mini_map_test(main);
	draw_player_test(main);

	int	ray_count = 0;
//*****************************************************************************
	
	angle = -1 * (FOV / 2.0);
	while (angle <= (FOV / 2.0))
	{
		raycasting(main, main->ply.rotation_angle + angle, ray_count);
		angle += (FOV / 2.0) / ((FOV_THICKNESS - 1) / 2.0);
		ray_count++;
	}

//*****************************************************************************


//-----------------------------------------------------------------------------
	// double angle;

	// angle = -1 * (FOV / 2.0);
	// while (angle <= (FOV / 2.0))
	// {
	// 	ray(main, main->ply.rotation_angle + angle);
	// 	angle += (FOV / 2.0) / ((FOV_THICKNESS - 1) / 2.0);
	// }
//-----------------------------------------------------------------------------
	// draw_player_directory(main);
	mlx_put_image_to_window(main->mlx.ptr, main->mlx.win,
		main->mini_map.ptr, 0, 0);
	return (0);
}

void	cub3d(t_main *main)
{
	if (minilibx_init(main) != ERROR)
	{
		int	x;
		int	y;

		where_is_my_hero(&x, &y, main);
		main->ply.x = x + 0.5;
		main->ply.y = y + 0.5;
		main->backup_ply_x = main->ply.x;
		main->backup_ply_y = main->ply.y;
		main->backup_ply_angle = main->ply.rotation_angle;
		main->ply.thickness = BOX_SIZE / PLAYER_THICKNESS;
		main->ply.walk_speed = PLAYER_WALKSPEED;
		printf("MAX_X:%d MAX_Y:%d\n", main->max_x, main->max_y);
		printf("ply_x:%f ply_y:%f\n", main->ply.x, main->ply.y);

		main->key.left = false;
		main->key.right = false;
		main->key.up = false;
		main->key.down = false;
		main->key.r_left = false;
		main->key.r_right = false;

		mlx_hook(main->mlx.win, 2, 1L<<0, &key_press, main);
		mlx_hook(main->mlx.win, 3, 1L<<1, &key_release, main);
		mlx_hook(main->mlx.win, 17, (0L), &ft_exit, main);
		mlx_loop_hook(main->mlx.ptr, ft_loop, main);
		mlx_loop(main->mlx.ptr);
	}
}
