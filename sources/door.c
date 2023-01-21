/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:53:41 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 01:16:04 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_door_open_or_close(t_main *main, double x, double y)
{
	int	x_x;
	int	y_y;

	if (main->key.door_open_command == true)
	{
		x_x = floor(x);
		y_y = floor(y);
		if (is_wall(main, x, y) == HIT)
		{
			printf("HEDEF\n");
			if (main->map.map[y_y][x_x] == 'O')
				main->map.map[y_y][x_x] = 'C';
			else if (main->map.map[y_y][x_x] == 'C')
				main->map.map[y_y][x_x] = 'O';
			printf("Location: map[%d][%d]=%c\n", x_x, y_y,
				main->map.map[y_y][x_x]);
			main->key.door_open_command = false;
		}
	}
}