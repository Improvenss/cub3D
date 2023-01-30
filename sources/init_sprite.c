/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:38:13 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 23:22:27 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_hitler_img(t_main *main)
{
	int	i;

	i = 0;
	while (++i <= 13)
	{
		main->xpm[TEXTURE_N + i].img.ptr = mlx_xpm_file_to_image(
				main->mlx.ptr,
				main->texture.sprite_hitler[i],
				&main->xpm[TEXTURE_N + i].width,
				&main->xpm[TEXTURE_N + i].height);
		main->xpm[TEXTURE_N + i].img.addr = (int *)mlx_get_data_addr(
				main->xpm[TEXTURE_N + i].img.ptr,
				&main->xpm[TEXTURE_N + i].img.bpp,
				&main->xpm[TEXTURE_N + i].img.line_size,
				&main->xpm[TEXTURE_N + i].img.endian);
	}
}

void	init_hitler_xpm(t_main *main)
{
	main->texture.sprite_hitler[0] = "./textures/hitler_4k/frame_00.xpm";
	main->texture.sprite_hitler[1] = "./textures/hitler_4k/frame_01.xpm";
	main->texture.sprite_hitler[2] = "./textures/hitler_4k/frame_02.xpm";
	main->texture.sprite_hitler[3] = "./textures/hitler_4k/frame_03.xpm";
	main->texture.sprite_hitler[4] = "./textures/hitler_4k/frame_04.xpm";
	main->texture.sprite_hitler[5] = "./textures/hitler_4k/frame_05.xpm";
	main->texture.sprite_hitler[6] = "./textures/hitler_4k/frame_06.xpm";
	main->texture.sprite_hitler[7] = "./textures/hitler_4k/frame_07.xpm";
	main->texture.sprite_hitler[8] = "./textures/hitler_4k/frame_08.xpm";
	main->texture.sprite_hitler[9] = "./textures/hitler_4k/frame_09.xpm";
	main->texture.sprite_hitler[10] = "./textures/hitler_4k/frame_10.xpm";
	main->texture.sprite_hitler[11] = "./textures/hitler_4k/frame_11.xpm";
	main->texture.sprite_hitler[12] = "./textures/hitler_4k/frame_12.xpm";
	main->texture.sprite_hitler[13] = "./textures/hitler_4k/frame_13.xpm";
	init_hitler_img(main);
}
