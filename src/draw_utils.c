/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:35:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 14:33:25 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_textured_wall(t_game *game, t_ray *ray, int x, int y)
{
	int		tex_index;
	int		tex_y;
	int		color;
	double	tex_pos;
	int		line_height;

	tex_index = get_wall_texture_index(ray);
	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	tex_pos = (y - SCREEN_HEIGHT / 2 + line_height / 2)
		* game->textures[tex_index].height / line_height;
	tex_y = (int)tex_pos;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->textures[tex_index].height)
		tex_y = game->textures[tex_index].height - 1;
	color = get_texture_pixel(&game->textures[tex_index], ray->tex_x, tex_y);
	put_pixel_to_image(&game->screen_buffer, x, y, color);
}

static void	draw_wall_pixel(t_game *game, t_ray *ray, int x, int y)
{
	int	tex_index;
	int	draw_start;
	int	draw_end;
	int	line_height;

	if (ray->perp_wall_dist <= 0.0)
		ray->perp_wall_dist = 0.001;
	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	tex_index = get_wall_texture_index(ray);
	if (y < draw_start)
		put_pixel_to_image(&game->screen_buffer, x, y,
			game->map.ceiling_color);
	else if (y <= draw_end && game->textures[tex_index].img_ptr)
		draw_textured_wall(game, ray, x, y);
	else if (y <= draw_end)
		put_pixel_to_image(&game->screen_buffer, x, y, 0x00FFFFFF);
	else
		put_pixel_to_image(&game->screen_buffer, x, y,
			game->map.floor_color);
}

static void	setup_texture_coords(t_game *game, t_ray *ray, int tex_index)
{
	if (game->textures[tex_index].img_ptr)
	{
		ray->tex_x = (int)(ray->wall_x * game->textures[tex_index].width);
		if (ray->side == 0 && ray->dir_x > 0)
			ray->tex_x = game->textures[tex_index].width - ray->tex_x - 1;
		if (ray->side == 1 && ray->dir_y < 0)
			ray->tex_x = game->textures[tex_index].width - ray->tex_x - 1;
	}
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	tex_index;
	int	y;

	if (ray->perp_wall_dist <= 0.0)
		ray->perp_wall_dist = 0.001;
	tex_index = get_wall_texture_index(ray);
	setup_texture_coords(game, ray, tex_index);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		draw_wall_pixel(game, ray, x, y);
		y++;
	}
}
