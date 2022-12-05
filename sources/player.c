/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:05:27 by gsever            #+#    #+#             */
/*   Updated: 2022/12/05 13:48:36 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	where_is_my_player(t_main *main, int x, int y)
{
	y = -1;
	while (main->map.map[++y])
	{
		x = -1;
		while (main->map.map[y][++x])
		{
			if (ft_strchr("ENWS", main->map.map[y][x]))
			{
				if (main->map.map[y][x] == 'E')
					main->ply.angle = 0;
				else if (main->map.map[y][x] == 'N')
					main->ply.angle = 90;
				else if (main->map.map[y][x] == 'W')
					main->ply.angle = 180;
				else if (main->map.map[y][x] == 'S')
					main->ply.angle = 270;
				main->map.map[y][x] = '0';
				main->ply.pos_x = x;
				main->ply.pos_y = y;
				return ;
			}
		}
	}
	return ;
}

// void	update_player_position(t_main *main)
// {

// 	return ;
// }