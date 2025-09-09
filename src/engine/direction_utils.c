/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:52:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 10:52:01 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_dir_config	create_dir_config(double dir_x, double dir_y,
		double plane_x, double plane_y)
{
	t_dir_config	config;

	config.dir_x = dir_x;
	config.dir_y = dir_y;
	config.plane_x = plane_x;
	config.plane_y = plane_y;
	return (config);
}

t_dir_config	get_north_config(void)
{
	return (create_dir_config(0.0, -1.0, CAMERA_PLANE_DISTANCE, 0.0));
}

t_dir_config	get_south_config(void)
{
	return (create_dir_config(0.0, 1.0, -CAMERA_PLANE_DISTANCE, 0.0));
}

t_dir_config	get_east_config(void)
{
	return (create_dir_config(1.0, 0.0, 0.0, CAMERA_PLANE_DISTANCE));
}

t_dir_config	get_west_config(void)
{
	return (create_dir_config(-1.0, 0.0, 0.0, -CAMERA_PLANE_DISTANCE));
}
