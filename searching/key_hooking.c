/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:36:13 by gsever            #+#    #+#             */
/*   Updated: 2022/11/15 21:22:32 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libraries/minilibx_opengl/mlx.h"

typedef struct s_mlx_key_hooking
{
	void	*mlx;
	void	*win;
}		t_mlx_key_hooking;

int	key_hook(t_mlx_key_hooking *main, int key)
{
	(void)main;
	printf("We catch this key's value --> %d\n", key);
	return (0);
}

int	main()
{
	t_mlx_key_hooking	main;
	
	main.mlx = mlx_init();
	printf("MLX initialized, creating new window.\n");
	main.win = mlx_new_window(main.mlx, 500, 500, "Key Hooking :)");
	// printf("Can we hook a any key?\n");
	// mlx_key_hook(main.mlx, key_hook, &main);
	mlx_hook(main.mlx, 2, 0, key_hook, &main);
	mlx_loop(main.mlx);
	return (0);
}