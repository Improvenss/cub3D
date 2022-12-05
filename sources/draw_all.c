/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:18:29 by gsever            #+#    #+#             */
/*   Updated: 2022/12/05 13:49:08 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_text_on_window(t_main *main)
{
	mlx_string_put(main->mlx->ptr, main->mlx->win,
		WINDOW_W - 80, WINDOW_H - 20, COLOR_TUNDORA, "H - Help");// Burasi H tusuna bastigimizda help ekrani acilacak. onun icin. Belki bunu ayarlar icin sekme flaan da yapabilirisz simdilik boyle dusundum.
	mlx_string_put(main->mlx->ptr, main->mlx->win, WINDOW_W - 80,
		WINDOW_H - 20 - 100, COLOR_TUNDORA, ft_itoa(main->key.value));
}

int	loop_draw_image_to_window(t_main *main)
{
	t_mlx	*mlx;

	mlx = main->mlx;
	printf("player before x[%f] y[%f]\n", main->ply.pos_x, main->ply.pos_y);
	where_is_my_player(main, 0, 0);
	//update_player_position(main);yapilacak
	printf("player after x[%f] y[%f]\n", main->ply.pos_x, main->ply.pos_y);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
	draw_text_on_window(main);
	return (0);
}

int	draw_mlx_window(t_main *main)
{
	mlx_loop_hook(main->mlx->ptr, loop_draw_image_to_window, main);
	return (0);
}