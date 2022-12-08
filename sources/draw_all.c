/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:18:29 by gsever            #+#    #+#             */
/*   Updated: 2022/12/08 02:48:36 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_with_ray_casting(t_main *main)
{
	sent_ray(main);
	mlx_put_image_to_window(main->mlx->ptr,
		main->mlx->win, main->mlx->img.ptr, 0, 0);
	// mlx_put_image_to_window(main->minimap)
	return ;
}

void	draw_text_on_window(t_main *main)
{
	mlx_string_put(main->mlx->ptr, main->mlx->win,
		WINDOW_W - 80, WINDOW_H - 20, COLOR_TUNDORA, "H - Help");// Burasi H tusuna bastigimizda help ekrani acilacak. onun icin. Belki bunu ayarlar icin sekme flaan da yapabilirisz simdilik boyle dusundum.
	mlx_string_put(main->mlx->ptr, main->mlx->win, WINDOW_W - 80,
		WINDOW_H - 20 - 100, COLOR_TUNDORA, ft_itoa(main->key.value));
}

int	loop_draw_image_to_window(t_main *main)
{
	update_player_all(main);
	draw_with_ray_casting(main);
	draw_text_on_window(main);// txt put to window
	printf("player x[%f] y[%f]", main->ply.pos_x, main->ply.pos_y);
	printf("ply.angle[%f]\n", main->ply.angle);
	return (0);
}

int	draw_mlx_window(t_main *main)
{
	mlx_loop_hook(main->mlx->ptr, loop_draw_image_to_window, main);
	return (0);
}