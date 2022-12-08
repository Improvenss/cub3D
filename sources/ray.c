/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:04:56 by gsever            #+#    #+#             */
/*   Updated: 2022/12/08 04:03:45 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_calc_distance(t_main *main, double angle)
{
	(void)main;
	(void)angle;
}

void	sent_ray(t_main *main)
{
	double	angle;
	double	final_angle;

	angle = main->ply.angle - (ONE_DEGREE * 33);
	final_angle = angle + (ONE_DEGREE * 66);
	printf(B_CYAN"start ray_casting while -> angle[%f], final_angle[%f]\n"END, angle, final_angle);
	while (angle < final_angle)
	{
		printf("angle[%f]\n", angle);
		// ray_init(&main->ray);
		// ray_calc_distance(&main, angle);
		// draw_minimap(main);
		// draw_rendered_player_eye(main);
		angle += ONE_DEGREE;
	}
	return ;
}

void	ray_init(t_ray *ray)
{
	ray->pos_x = 0;
	ray->pos_y = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->max_x = 0;
	ray->max_y = 0;
}