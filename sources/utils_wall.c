/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:53:55 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 02:40:06 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	next_step_is_wall(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	if (x < 0 || x > main->map.max_x || y < 0 || y > main->map.max_y)
		return (1);
	x_x = floor(x);
	y_y = floor(y);
	// printf("xX:%d, yY:%d\n", x_x, y_y);
	// if (main->map.map[y_y][x_x] != '1' main->map.map[y_y][x_x] != 'M')
	// if ()
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)// playerimizin konumu icin genellikle
		return (0);
	return (1);
}

int	is_wall(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	if (x < 0 || x > main->map.max_x || y < 0 || y > main->map.max_y)
		return (1);
	x_x = floor(x);
	y_y = floor(y);
	// printf("xX:%d, yY:%d\n", x_x, y_y);
	// if (main->map.map[y_y][x_x] != '1' main->map.map[y_y][x_x] != 'M')
	// if ()
	if (ft_strchr(MAP_PLY_CANT_GO, main->map.map[y_y][x_x]) == NULL)// playerimizin konumu icin genellikle
		return (0);
	return (1);
}

int is_wall_v2(t_main *main, double x, double y)
{
	int xX;
	int yY;

	xX = (int)floor(x);
	yY = (int)floor(y);
	if (ft_strchr("MZ", main->map.map[yY][xX]))
	{
		main->sprite.is_hit = true;
		main->sprite.s_x = xX + 0.5;
		main->sprite.s_y = yY + 0.5;
		if (main->sprite.distance == 0)
			main->sprite.distance = sqrt(((main->ply.pos_x - main->sprite.s_x)*(main->ply.pos_x - main->sprite.s_x)) + ((main->ply.pos_y - main->sprite.s_y)*(main->ply.pos_y - main->sprite.s_y)));
	}
	return (ft_strchr(MAP_RAY_CAN_GO, main->map.map[yY][xX]) == NULL);// isinimiz bunlarin icinden gecebilir, haricindekilerden gecemez//return (ft_strchr("0NSEWMZ", main->map.map[yY][xX]) == NULL);
}


// int is_wall_v2(t_main *main, double x, double y)
// {
// 	int xX;
// 	int yY;

// 	xX = (int)floor(x);
// 	yY = (int)floor(y);
// 	return (ft_strchr("0NSEW", main->map.map[yY][xX]) == NULL);//return (ft_strchr("0NSEW", main->map.map[yY][xX]) == NULL);
// }