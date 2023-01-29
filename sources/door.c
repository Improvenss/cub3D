/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:53:41 by gsever            #+#    #+#             */
/*   Updated: 2023/01/29 22:33:59 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_which_texture_put(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	x_x = (int)floor(x);
	y_y = (int)floor(y);
	if (main->map.map[y_y][x_x] == '1')
		main->xpm_number = -1;
	else if (main->map.map[y_y][x_x] == 'C')
		main->xpm_number = 4;
	else if (main->map.map[y_y][x_x] == 'Z')
		main->xpm_number_sprite = 5;
	else if (main->map.map[y_y][x_x] == 'M')
		main->xpm_number_sprite = 6;
		// printf("main_icindeki->xpm_number[%d]\n", main->xpm_number);
}

void	check_door_open_or_close(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	if (main->key.door_open_command == true)
	{
		x_x = (int)floor(x);
		y_y = (int)floor(y);
		if (is_wall(main, x, y, -123.0) == HIT)
		{
			if (ft_strchr("C", main->map.map[y_y][x_x]))
			{
				if (main->map.map[y_y][x_x] == 'C')
					main->map.map[y_y][x_x] = 'O';
				printf(GREEN"Door Opened: map[%d][%d]=%c, ray_hit_location[x:%f][y:%f]\n"END, x_x, y_y,
					main->map.map[y_y][x_x], x, y);
			}
			else if (!ft_strchr("O", main->map.map[y_y][x_x]))
				printf("Location: map[%d][%d]=%c, ray_hit_location[x:%f][y:%f]\n"END, x_x, y_y,
					main->map.map[y_y][x_x], x, y);
		}
		main->key.door_open_command = false;
	}
}
