/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:31:12 by akaraca           #+#    #+#             */
/*   Updated: 2023/01/11 17:52:35 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	minilibx_init(t_main *main)
{
	main->mlx.ptr = mlx_init();
	if (main->mlx.ptr == NULL)
		return (err(RED"mlx_init() func. error"END));
// ____________________WINDOW CREATING_________________________________________
	main->mlx.win = mlx_new_window(main->mlx.ptr, WINDOW_W, WINDOW_H, PROMPT);// window creating
	if (main->mlx.win == NULL)
	{
		linux_mlx_free(main);
		return (err(RED"mlx_new_window() func. error"END));
	}
// ____________________________________________________________________________
// ____________________WINDOW SCREEN IMG CREATING_____________________________
	main->screen.ptr = mlx_new_image(main->mlx.ptr, (int)(WINDOW_W), (int)(WINDOW_H));
	if (main->screen.ptr == NULL)
	{
		mlx_destroy_window(main->mlx.ptr, main->mlx.win);
		linux_mlx_free(main);
		return (err(RED"mlx_new_image() func. error"END));
	}
	main->screen.addr = (int *)mlx_get_data_addr(main->screen.ptr, &main->screen.bpp,
			&main->screen.line_size, &main->screen.endian);
// ____________________________________________________________________________
// ____________________WINDOW minimap IMG CREATING_____________________________
	main->mini_map.ptr = mlx_new_image(main->mlx.ptr, BOX_SIZE * (main->max_x+1), BOX_SIZE * (main->max_y+1));
	main->mini_map.addr = (int *)mlx_get_data_addr(main->mini_map.ptr, &main->mini_map.bpp,
			&main->mini_map.line_size, &main->mini_map.endian);
// ____________________________________________________________________________
	return (0);
}

// int	minilibx_init(t_main *main)
// {
// 	main->mlx.ptr = mlx_init();
// 	if (main->mlx.ptr == NULL)
// 		return (err(RED"mlx_init() func. error"END));
// 	main->mlx.win = mlx_new_window(main->mlx.ptr, WINDOW_W, WINDOW_H, PROMPT);
// 	if (main->mlx.win == NULL)
// 	{
// 		linux_mlx_free(main);
// 		return (err(RED"mlx_new_window() func. error"END));
// 	}
// 	main->img.ptr = mlx_new_image(main->mlx.ptr, (int)(WINDOW_W), (int)(WINDOW_H));
// 	if (main->img.ptr == NULL)
// 	{
// 		mlx_destroy_window(main->mlx.ptr, main->mlx.win);
// 		linux_mlx_free(main);
// 		return (err(RED"mlx_new_image() func. error"END));
// 	}
// 	main->img.addr = (int *)mlx_get_data_addr(main->img.ptr, &main->img.bpp,
// 			&main->img.line_size, &main->img.endian);
// 	return (0);
// }
