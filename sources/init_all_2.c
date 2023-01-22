/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:23:45 by gsever            #+#    #+#             */
/*   Updated: 2023/01/22 17:29:13 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_all_xpm_others(t_main *main)
{
	main->texture.crosshair = "./textures/crosshair_green.xpm";
	main->xpm[7].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.crosshair, &main->xpm[7].width, &main->xpm[7].height);
}

void	init_all_xpm_sprites(t_main *main)
{
	main->texture.door = "./textures/spider_door.xpm";
	main->xpm[4].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.door, &main->xpm[4].width, &main->xpm[4].height);
	main->texture.sprite[0] = "./textures/tonneau.xpm";
	main->xpm[5].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.sprite[0], &main->xpm[5].width, &main->xpm[5].height);
	main->texture.sprite[1] = "./textures/niggachu_64px.xpm";
	main->xpm[6].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.sprite[1], &main->xpm[6].width, &main->xpm[6].height);
}

/**
 * @brief 
 * 
 * [0-1-2-3] = Walls,
 * [4] = Door,
 * [5-6] = Sprites,
 * [7] = Crosshair.
 * @param main 
 * @return int 
 */
int	init_all_xpm_files(t_main *main)
{
	int	i;

	main->xpm[0].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.no, &main->xpm[0].width, &main->xpm[0].height);
	main->xpm[1].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.so, &main->xpm[1].width, &main->xpm[1].height);
	main->xpm[2].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.ea, &main->xpm[2].width, &main->xpm[2].height);
	main->xpm[3].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.we, &main->xpm[3].width, &main->xpm[3].height);
	init_all_xpm_sprites(main);
	init_all_xpm_others(main);
	i = -1;
	while (++i < 7)
		main->xpm[i].img.addr = (int *)mlx_get_data_addr(main->xpm[i].img.ptr,
				&main->xpm[i].img.bpp, &main->xpm[i].img.line_size,
				&main->xpm[i].img.endian);
	return (0);
}

/**
 * @brief 
 * 
	// main->ray.is_sprite[0] = false;
	// main->ray.is_sprite[1] = false;
	// main->ray.is_door = false;
 * @param main 
 * @return int 
 */
int	init_mlx_draw(t_main *main)
{
	init_set_player(main, 0, 0);
	main->ply.walk_speed = PLAYER_WALK_SPEED;
	main->key.screen_mid = (WINDOW_H / 2);
	main->key.value = 0;
	main->mouse.is_enable = false;
	main->key.door_open_command = false;
	return (0);
}
