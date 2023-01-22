/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:33:44 by gsever            #+#    #+#             */
/*   Updated: 2023/01/23 00:46:12 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlximg *img, int x, int y, int color)
{
	int	*dest;

	dest = img->addr + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}