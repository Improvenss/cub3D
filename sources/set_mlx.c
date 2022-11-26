/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:01:10 by gsever            #+#    #+#             */
/*   Updated: 2022/11/26 23:49:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_pixe(double x, int y, double color, t_mlximg *img, t_main *main)
{
	int i;
	int j;

	i = -1;
	while (++i < main->box_size)
	{
		j = -1;
		while (++j < main->box_size)
		{
			img->addr[(int)(WINDOW_W * (y + i) + (x + j))] = color;
		}
	}
}

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
				put_pixe(main->box_size  * x, main->box_size  * y, 0xffffff, &(main->mlx->img), main);
			else if (main->map[y][x] == '0')
				put_pixe(main->box_size  * x, main->box_size  * y, 0x000000, &(main->mlx->img), main);
			else
				put_pixe(main->box_size  * x, main->box_size  * y, 0x000000, &(main->mlx->img), main);
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
			main->mlx->img.addr[(int)(WINDOW_W) * (int)(main->box_size * main->ply.y + y) + (int)(main->box_size * main->ply.x + x)] = 0xff0000;
			x++;
		}
		y++;
	}
}

void draw_player_directory(t_main *main)
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

void draw_ray(t_main *main, double angle)
{
	double ydy;
	double ydx;

	//int x = main->ply.rotationAngle + 180;
	// if (x > 0 && x <= 180)
	// 	ydx = main->ply.x - ceil(main->ply.x);
	// else
	// 	ydx = main->ply.x + ceil(main->ply.x);
	// // if (tan(((FOV / 2) + x) * (PI / 180)) != 0)
	// // 	ydy = ydx / tan(((FOV / 2) + x) * (PI / 180));
	// // else
	// // {
	ydy = 1 * sin((angle - (FOV / 2)) * (M_PI / 180));
	ydx = 1 * cos((angle - (FOV / 2)) * (M_PI / 180));
	// }
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
	//printf("x:%f y:%f\n", ray_x, ray_y);
}

/** Dikey
 * @brief Dikey
 * 
 * @param main 
 * @param angle 
 */
void	draw_vertical(t_main *main, double angle)
{
	double ydx;
	double ydy;

	ydx = ceil(main->ply.x) - main->ply.x;
	ydy = ydx * tan(((angle - (FOV / 2)) * (M_PI / 180)));
	while (1)
	{
		if (!is_wall(floor(main->ply.x + ydx), floor(main->ply.y - ydy), main))
		{
			ydx = ydx + 1;
			ydy = ydx * tan(((angle - (FOV / 2)) * (M_PI / 180)));
		}
		else// Hit the wall
			break;
	}
	if (main->ply.y - ydy < 1)
	{
		ydx = ydx - 1;
		ydy = ydx * tan(((angle - (FOV / 2)) * (M_PI / 180)));
		if (ydx < 0)
		{
			ydx = 0;
			ydy = 0;
		}
	}
	double hitX = main->ply.x + ydx;
	double hitY = main->ply.y - ydy;
	main->ray.mesafe = sqrt(ydx * ydx + ydy * ydy);
	main->ray.x = hitX;
	main->ray.y = hitY;
	//main->mlx->img.addr[WINDOW_W * (int)floor(main->box_size * (hitY)) + (int)floor(main->box_size * (hitX))] = 0xff0000;
	//printf("ydx:%f ydy:%f x:%f y:%f \n", hitX, hitY, main->ply.x, main->ply.y);
}

/** Yatay
 * @brief Yatay
 * 
 * @param main 
 * @param angle 
 */
void draw_horizon(t_main *main, double angle)
{
	double ydy;
	double ydx;

	ydy = main->ply.y - floor(main->ply.y);
	ydx = ydy / tan(((angle - (FOV / 2)) * (M_PI / 180)));
	while (1)
	{
		if (!is_wall(floor(main->ply.x + ydx), floor(main->ply.y - ydy), main))
		{
			ydy = ydy + 1;
			ydx = ydy / tan(((angle - (FOV / 2)) * (M_PI / 180)));
		}
		else
			break;
	}
	if (is_wall(floor(main->ply.x + ydx), floor(main->ply.y - ydy), main))
	{
		ydy = ydy - 1;
		ydx = ydy / tan(((angle - (FOV / 2)) * (M_PI / 180)));
		if (ydx < 0)
		{
			ydx = 0;
			ydy = 0;
		}
	}
	double hitX = main->ply.x + ydx;
	double hitY = main->ply.y - ydy;
	double mesafe_horizon = sqrt(ydx*ydx + ydy*ydy);
	if (mesafe_horizon > main->ray.mesafe)
	{
		main->ray.mesafe = mesafe_horizon;
		main->ray.x = hitX;
		main->ray.y = hitY;
	}
	//main->mlx->img.addr[WINDOW_W * (int)floor(main->box_size * (hitY)) + (int)floor(main->box_size * (hitX))] = 0xFF0000;
	//printf("ydx:%f ydy:%f x:%f y:%f \n", hitX, hitY, main->ply.x, main->ply.y);

}

void draw_ray_ikinci_deneme(t_main *main, double angle)
{
	draw_vertical(main, angle);
	draw_horizon(main, angle);
	// (void)angle;

	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_value;
	
	ray_x = main->ply.x;
	ray_y = main->ply.y;
	dx = main->ray.x - main->ply.x;
	dy = main->ray.y - main->ply.y;

	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(ray_x, ray_y, main))
			main->mlx->img.addr[WINDOW_W * (int)floor(main->box_size * ray_y) + (int)floor(main->box_size * ray_x)] = 0xFF0000;
		else
			break;
		ray_x += dx / 2000;
		ray_y += dy / 2000;
	}
	//printf("mesafe:%f x:%f y:%f\n", main->ray.mesafe, main->ray.x, main->ray.y);

}

int ft_loop(t_main *main)
{
	draw_minimap_test(main);
	draw_player_test(main);

	// double angle;
	// double maxangle;

	// angle = main->ply.rotationAngle + 180;
	// maxangle = angle + (FOV / 2.0);
	// while (angle <= maxangle)
	// {
	// 	draw_ray(main, angle);
	// 	draw_ray(main, angle + (FOV / 2.0));
	// 	angle += (FOV / 2.0) / ((FOV_THICKNESS - 1) / 2.0);
	// }

	double angle;
	double maxangle;

	angle = main->ply.rotationAngle;
	maxangle = angle + (FOV / 2.0);// +30º
	// printf("maxangle[%fº]\n", maxangle);
	while (angle <= maxangle)
	{
		// draw_ray_ikinci_deneme(main, angle);// right side 30º
		// draw_ray_ikinci_deneme(main, angle + (FOV / 2.0));// left side 30º
		draw_ray(main, angle);
		draw_ray(main, angle + (FOV / 2.0));
		angle += (FOV / 2.0) / ((FOV_THICKNESS) / 2.0);// angle += 30 / 60; -> 0.5;
	}
	draw_player_directory(main);
	mlx_put_image_to_window(main->mlx->ptr, main->mlx->win,
		main->mlx->img.ptr, 0, 0);
	mlx_string_put(main->mlx->ptr, main->mlx->win,
		WINDOW_W - 80, WINDOW_H - 20, COLOR_TUNDORA, "H - Help");// Burasi H tusuna bastigimizda help ekrani acilacak. onun icin. Belki bunu ayarlar icin sekme flaan da yapabilirisz simdilik boyle dusundum.
	mlx_string_put(main->mlx->ptr, main->mlx->win,
		WINDOW_W - 80, WINDOW_H - 20 - 50, COLOR_TUNDORA, ft_itoa(main->ply.rotationAngle));
	return (0);
}

int	window_draw(t_main *main)
{
	int	x;
	int	y;
	where_is_my_hero(&x, &y, main);
	main->ply.x = x + 0.5;
	main->ply.y = y + 0.5;
	main->ply.thickness = PLAYER_THICKNESS;
	main->ply.walkSpeed = PLAYER_WALKSPEED;
	//printf("W_X:%d W_Y:%d RATE:%d\n", WINDOW_W , WINDOW_H, SCREEN_RATE);
	// double M_Y = WINDOW_H / SCREEN_RATE;
	// double M_X = WINDOW_W / SCREEN_RATE;
	// printf("M_X:%f M_Y:%f\n", M_X, M_Y);
	// double B_Y = ceil(M_Y / main->max_y);
	// double B_X = ceil(M_X / main->max_x);
	// printf("B_X:%f B_Y:%f\n", B_X, B_Y);
	printf("MAX_X:%d MAX_Y:%d\n", main->max_x, main->max_y);
	// printf("x:%f y:%f\n", main->ply.x, main->ply.y);
	//draw_minimap_test(main);
	//draw_player_test(main);
	mlx_loop_hook(main->mlx->ptr, ft_loop, main);
	return (0);
}

int	window_init(t_main *main)
{
	t_mlx	*mlx;

	main->mlx = malloc(sizeof(t_mlx));
	if (main->mlx == NULL)
		return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	mlx = main->mlx;
	mlx->ptr = mlx_init();
	if (mlx->ptr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_init() error."));
	mlx->win = mlx_new_window(mlx->ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (mlx->win == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_new_window() error."));
	mlx->img.ptr = mlx_new_image(mlx->ptr, WINDOW_W, WINDOW_H);
	if (mlx->img.ptr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_new_image() error."));
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	if (mlx->img.addr == NULL)
		return (print_error(PROMPT, NULL, NULL, "mlx_get_data_addr() error."));
	mlx_hook(mlx->win, 2, 1L<<0, &actions_key, main);
	mlx_hook(mlx->win, 4, 0, &actions_mouse, main);
	mlx_hook(mlx->win, 17, 0, &mlx_free_kill_all, main);// close_window(); yapilacak
	return (0);
}

int	window_set(t_main *main)
{
	if (window_init(main) == ERROR)
		return (ERROR);
	if (window_draw(main) == ERROR)
		return (ERROR);
	return (0);
}
