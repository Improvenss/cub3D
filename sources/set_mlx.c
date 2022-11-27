/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:01:10 by gsever            #+#    #+#             */
/*   Updated: 2022/11/27 07:48:10 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void put_pixe(t_main *main, double x, int y, double color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < main->box_size)
	{
		j = -1;
		while (++j < main->box_size)
		{
			main->mlx->img.addr[(int)(WINDOW_W * (y + i) + (x + j))] = color;
		}
	}
}

int ft_loop(t_main *main)
{
	// run_ray_casting(main);
	update_player(main);
	draw_render(main);
	draw_minimap(main);
	mlx_put_image_to_window(main->mlx->ptr, main->mlx->win,
		main->mlx->img.ptr, 0, 0);
	mlx_string_put(main->mlx->ptr, main->mlx->win,
		WINDOW_W - 80, WINDOW_H - 20, COLOR_TUNDORA, "H - Help");// Burasi H tusuna bastigimizda help ekrani acilacak. onun icin. Belki bunu ayarlar icin sekme flaan da yapabilirisz simdilik boyle dusundum.
	mlx_string_put(main->mlx->ptr, main->mlx->win, WINDOW_W - 80,
		WINDOW_H - 20 - 50, COLOR_TUNDORA, ft_itoa(main->ply.rotationAngle));
	return (0);
}

int	window_draw(t_main *main)
{
	int	x;
	int	y;
	where_is_my_hero(&x, &y, main);
	main->ply.x = x + 0.5;
	main->ply.y = y + 0.5;
	// main->ply.thickness = PLAYER_THICKNESS;// bunlari kapadim cunku kutuphanede tanimli zaten gerek yok :D.
	// main->ply.walkSpeed = PLAYER_WALKSPEED;
	printf("MAX_X:%d MAX_Y:%d\n", main->max_x, main->max_y);
	// printf("x:%f y:%f\n", main->ply.x, main->ply.y);
	mlx_loop_hook(main->mlx->ptr, ft_loop, main);
	return (0);
}

int	window_set(t_main *main)
{
	if (window_draw(main) == ERROR)
		return (ERROR);
	return (0);
}
