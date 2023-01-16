/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:48:49 by gsever            #+#    #+#             */
/*   Updated: 2023/01/16 16:32:44 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * 
 * Gerekli argler:
 * 	 Hangi duvara carptiginin bilinmesi gerekiyor;
 * 		dir_x, dir_y, hit_v, hit_h, hit_x, hit_y
 * @param main 
 * @param location 
 * @param color 
 */
void	draw_xpm_to_wall(t_main *main, int location)
{
	int	color;

	if (main->ray.hit_h == true && main->ray.dir_y == -1)//kuzey -> no
	{
		color = main->xpm.
		main->screen.addr[location] = main->xpm[0].img.addr[color];
	}
	// main->screen.addr[location] = color;//ust taraf
}