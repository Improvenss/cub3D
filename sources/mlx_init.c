/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaraca <akaraca@student.42.tr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:31:12 by akaraca           #+#    #+#             */
/*   Updated: 2022/12/12 18:52:05 by akaraca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	minilibx_init(t_main *main)
{
	main->mlx.ptr = mlx_init();
	if (main->mlx.ptr == NULL)
		return (err(RED"mlx_init() func. error"END));
	main->mlx.win = mlx_new_window(main->mlx.ptr, WINDOW_W, WINDOW_H, PROMPT);
	if (main->mlx.win == NULL)
	{
		linux_mlx_free(main);
		return (err(RED"mlx_new_window() func. error"END));
	}
	main->img.ptr = mlx_new_image(main->mlx.ptr, (int)(WINDOW_W), (int)(WINDOW_H));
	if (main->img.ptr == NULL)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.win);
		linux_mlx_free(main);
		return (err(RED"mlx_new_image() func. error"END));
	}
	main->img.addr = (int *)mlx_get_data_addr(main->img.ptr, &main->img.bpp,
			&main->img.line_size, &main->img.endian);
	return (0);
}
