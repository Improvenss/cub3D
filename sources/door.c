/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:53:41 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 21:43:43 by gsever           ###   ########.fr       */
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
			if (ft_strchr("C", main->map.map[y_y][x_x]))
			{
				if (main->map.map[y_y][x_x] == 'C')
					main->map.map[y_y][x_x] = 'O';
				printf(GREEN"Door Opened: map[%d][%d]=%c\n"END, x_x, y_y,
					main->map.map[y_y][x_x]);
			}
			else if (!ft_strchr("O", main->map.map[y_y][x_x]))
				printf("Location: map[%d][%d]=%c\n"END, x_x, y_y,
					main->map.map[y_y][x_x]);
		}
		main->key.door_open_command = false;
		// if (is_wall(main, x, y) == HIT)
		// {
		// 	if (main->map.map[y_y][x_x] == 'C')
		// 		main->map.map[y_y][x_x] = 'O';
		// 	printf(GREEN"Door Opened: map[%d][%d]=%c\n"END, x_x, y_y,
		// 		main->map.map[y_y][x_x]);
		// 	main->key.door_open_command = false;
		// }
	}
}
