/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsever <gsever@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:07:22 by gsever            #+#    #+#             */
/*   Updated: 2022/11/14 17:16:26 by gsever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_cub3d(t_main *main)
{
	main = malloc(sizeof(t_main));
	if (main == NULL)
		return (print_error(PROMPT, NULL, NULL, strerror(errno)));
	return (0);
}