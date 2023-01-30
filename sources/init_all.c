/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 00:45:58 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 15:20:00 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Box size * width or height + 1;
 * 
 * @param main 
 * @return int 
 */
static int	init_minimap_image(t_main *main)
{
	main->mini_map.ptr = mlx_new_image(main->mlx.ptr, BOX_SIZE
			* (main->map.max_x + 1), BOX_SIZE * (main->map.max_y + 1));
	if (main->mini_map.ptr == NULL)
		return (print_error(PROMPT, "minimap", "mlx_new_image()", "error."));
	main->mini_map.addr = (int *)mlx_get_data_addr(main->mini_map.ptr,
			&main->mini_map.bpp,
			&main->mini_map.line_size, &main->mini_map.endian);
	if (main->mini_map.addr == NULL)
		return (print_error(PROMPT, "minimap",
				"mlx_get_data_addr()", "error."));
	return (0);
}

/**
 * @brief Minimap's image.
 * 
 * @param main 
 * @return int 
 */
static int	init_minimap(t_main *main)
{
	if (init_minimap_image(main) == ERROR)
		return (ERROR);
	return (0);
}

/**
 * @brief Initializing program headers in here.
 * 
 * @param main 
 * @return int 
 */
int	init_all(t_main *main)
{
	if (init_cub3d(main) == ERROR)
		return (ERROR);
	if (init_minimap(main) == ERROR)
		return (ERROR);
	if (init_mlx_draw(main) == ERROR)
		return (ERROR);
	if (init_all_xpm_files(main) == ERROR)
		return (ERROR);
	return (0);
}
