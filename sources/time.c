/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:59:34 by gsever            #+#    #+#             */
/*   Updated: 2023/01/30 13:07:49 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Get the or print time for fps object
 * 
 * @param main 
 * @param status if false; start time, if true, last time.
 */
void	get_or_print_time_for_fps(t_main *main, bool status)
{
	if (status == false)
		main->time.start_time = clock();
	else if (status == true)
	{
		main->time.now = clock();
		main->time.fps = (int)((FRAME_PER_SECOND)
			/ (main->time.now - main->time.start_time));
	}
}