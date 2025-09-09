/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:30:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 12:30:00 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calculate_texture_coordinates(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	get_wall_texture_index(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->dir_y > 0)
			return (TEXTURE_SOUTH);
		else
			return (TEXTURE_NORTH);
	}
	else
	{
		if (ray->dir_x > 0)
			return (TEXTURE_EAST);
		else
			return (TEXTURE_WEST);
	}
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(int *)pixel);
}
