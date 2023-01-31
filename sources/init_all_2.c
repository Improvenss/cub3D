/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:23:45 by gsever            #+#    #+#             */
/*   Updated: 2023/01/31 12:16:21 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Player's crosshair for rotation_angle way.
 * 
 * @param main 
 */
void	init_all_xpm_others(t_main *main)
{
	main->texture.crosshair = "./textures/crosshair_green.xpm";
	main->xpm[7].img.ptr = mlx_xpm_file_to_image(
			main->mlx.ptr,
			main->texture.crosshair,
			&main->xpm[7].width, &main->xpm[7].height);
}

/**
 * @brief Sprite and door.
 * 
 * @param main 
 * @fn init_all_animated_sprite(): 4k_hitler_gif to xpm.
 */
void	init_all_xpm_sprites(t_main *main)
{
	main->texture.door = "./textures/fbi_flying_door.xpm";
	main->xpm[4].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.door, &main->xpm[4].width, &main->xpm[4].height);
	main->texture.sprite[0] = "./textures/pikachu_64px.xpm";
	main->xpm[5].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.sprite[0],
			&main->xpm[5].width, &main->xpm[5].height);
	main->texture.sprite[1] = "./textures/tonneau.xpm";
	main->xpm[6].img.ptr = mlx_xpm_file_to_image(main->mlx.ptr,
			main->texture.sprite[1],
			&main->xpm[6].width, &main->xpm[6].height);
	init_all_xpm_others(main);
	init_hitler_xpm(main);
}

/**
 * @brief Converting textures to image, after getting images data.
 * 
 * main->xpm[?]
 * [0-1-2-3] = Walls,
 * [4] = Door,
 * [5-6] = Sprites,
 * [7] = Crosshair,
 * [8 to 21] = Hitler_animated.
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
	i = -1;
	while (++i < TEXTURE_N)
		main->xpm[i].img.addr = (int *)mlx_get_data_addr(main->xpm[i].img.ptr,
				&main->xpm[i].img.bpp, &main->xpm[i].img.line_size,
				&main->xpm[i].img.endian);
	return (0);
}

/**
 * @brief Initializing others.
 * 
 * @param main 
 * @fn init_set_player(): Reading .cub file and setting player's
 *  start location and rotation_angle.
 * @return int 0
 */
int	init_mlx_draw(t_main *main)
{
	init_set_player(main, 0, 0);
	main->ply.walk_speed = PLAYER_WALK_SPEED;
	main->key.screen_mid = (WINDOW_H / 2);
	main->key.value = 0;
	main->mouse.is_enable = false;
	main->key.door_open_command = false;
	main->key.show_mini_map = true;
	main->key.help_page = false;
	main->xpm_number = 0;
	main->xpm_number_sprite = 5;
	main->xpm_number_sprite_m = TEXTURE_N + 1;
	main->loop_count = 0;
	return (0);
}
