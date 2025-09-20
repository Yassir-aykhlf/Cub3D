/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:48:34 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:40:12 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray(t_ray *ray, t_player *player, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->wall_x = 0.0;
	ray->tex_x = 0;
}

void	calculate_dda_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

void	cast_single_ray(t_game *game)
{
	t_ray	ray;

	clear_screen(game);
	init_ray(&ray, &game->player, WINDOW_WIDTH / 2);
	calculate_dda_step_and_side_dist(&ray, &game->player);
	perform_dda(&ray, game);
	calculate_wall_distance(&ray, &game->player);
	if (game->textures[0].img_ptr)
		calculate_texture_coordinates(&ray, &game->player);
	draw_vertical_line(game, &ray, WINDOW_WIDTH / 2);
}

void	cast_all_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	clear_screen(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, &game->player, x);
		calculate_dda_step_and_side_dist(&ray, &game->player);
		perform_dda(&ray, game);
		calculate_wall_distance(&ray, &game->player);
		if (game->textures[0].img_ptr)
			calculate_texture_coordinates(&ray, &game->player);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
