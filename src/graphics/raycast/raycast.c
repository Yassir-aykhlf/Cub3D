/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 12:48:09 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	move_ray_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static int	check_wall_hit(t_ray *ray, t_game *game)
{
	if (ray->map_y < 0 || ray->map_y >= (int)game->map.grid.size
		|| ray->map_x < 0)
		return (1);
	if (ray->map_x >= (int)strlen(game->map.grid.items[ray->map_y]))
		return (1);
	if (game->map.grid.items[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	perform_dda(t_ray *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		move_ray_step(ray);
		if (check_wall_hit(ray, game))
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	if (ray->perp_wall_dist < 0)
		ray->perp_wall_dist = -ray->perp_wall_dist;
}
