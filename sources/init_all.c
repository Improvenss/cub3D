/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:45:58 by gsever            #+#    #+#             */
/*   Updated: 2022/12/13 13:21:33 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_mlx_draw(t_main *main)
{
	init_set_player(main, 0, 0);
	return (0);
}

// int	init_mlx_hooking(t_main *main)
// {
// 	ft_putstr_fd(B_CYAN"hooking() girildi \n"END, 1);
// 	mlx_hook(main->mlx->win, 2, 1L << 0, &key_press, main);
// 	ft_putstr_fd(B_CYAN"mlx_hook key_press OK\n"END, 1);
// 	mlx_hook(main->mlx->win, 3, 1L << 1, &key_release, main);
// 	// mlx_hook(mlx->win, 4, 0, &actions_mouse, main);
// 	mlx_hook(main->mlx->win, 17, 0, &mlx_free_kill_all, main);// close_window(); yapilacak
// 	return (0);
// }

static int	init_minimap(t_main *main)
{
	if ((MINIMAP_RATE_H / main->map.max_y)
		> (MINIMAP_RATE_W / main->map.max_x))
		main->minimap.box_size = MINIMAP_RATE_W / main->map.max_x;
	else
		main->minimap.box_size = MINIMAP_RATE_H / main->map.max_y;
	if (init_minimap_image(main) == ERROR)// image init area
		return (ERROR);
	return (0);
}

static int	init_cub3d(t_main *main)
{
	main = malloc(sizeof(t_main));
	if (main == NULL)
		return (print_error(PROMPT, "t_main", "main", strerror(errno)));
	main->mlx = malloc(sizeof(t_mlx));
	if (main->mlx == NULL)
		return (print_error(PROMPT, "t_mlx", "mlx", strerror(errno)));
	if (init_cub3d_window(main) == ERROR)// window init area
		return (ERROR);
	if (init_cub3d_image(main) == ERROR)// image init area
		return (ERROR);
	return (0);
}

int	init_all(t_main *main)
{
	if (init_cub3d(main) == ERROR)// malloc init area
		return (ERROR);
	if (init_minimap(main) == ERROR)// image init area
		return (ERROR);
	// if (init_mlx_hooking(main) == ERROR)// key, mouse, click hooking area
		// return (ERROR);
	if (init_mlx_draw(main) == ERROR)// ply_location...
		return (ERROR);
	return (0);
}