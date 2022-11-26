/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:54:44 by gsever            #+#    #+#             */
/*   Updated: 2022/11/18 16:30:09 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mlx_free_kill_all(t_main *main)
{
	(void)main;
	// if (main->mlx != NULL)
	// {
	// 	mlx_destroy_window(main->mlx->ptr, main->mlx->win);
	// 	mlx_destroy_image(main->mlx->ptr, main->mlx->img.ptr);
	// 	free(main->mlx);
	// }
	// free(main);
	exit(EXIT_SUCCESS);
}