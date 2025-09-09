/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:48:40 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 10:16:42 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_ceiling_and_floor(t_game *game, int x, int draw_start,
	int draw_end)
{
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < draw_start)
			put_pixel_to_image(&game->screen_buffer, x, y,
				game->map.ceiling_color);
		else if (y > draw_end)
			put_pixel_to_image(&game->screen_buffer, x, y,
				game->map.floor_color);
		y++;
	}
}

void	draw_wall_line(t_game *game, int x, int draw_start,
	int draw_end)
{
	int	y;

	y = draw_start;
	while (y <= draw_end)
	{
		put_pixel_to_image(&game->screen_buffer, x, y, 0x00FFFFFF);
		y++;
	}
}

void	clear_screen(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(&game->screen_buffer, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}
