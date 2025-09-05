/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:35:40 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 14:24:42 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_map_grid(t_game *game)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	color;

	y = 0;
	while (y < 100 && y / 10 < (int)game->map.grid.size)
	{
		map_y = y / 10;
		x = 0;
		while (x < 100
			&& x / 10 < (int)strlen(game->map.grid.items[map_y]))
		{
			map_x = x / 10;
			if (game->map.grid.items[map_y][map_x] == '1')
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			put_pixel_to_image(&game->screen_buffer, x + 10, y + 10, color);
			x++;
		}
		y++;
	}
}

static void	get_map_dimensions(t_game *game, int *map_width, int *map_height)
{
	*map_height = (int)game->map.grid.size;
	*map_width = 0;
	if (*map_height > 0)
		*map_width = (int)strlen(game->map.grid.items[0]);
}

static void	draw_player_dot(t_game *game, int player_x, int player_y)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (player_x + i >= 10 && player_x + i < 110
				&& player_y + j >= 10 && player_y + j < 110)
				put_pixel_to_image(&game->screen_buffer,
					player_x + i, player_y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_game *game)
{
	int	player_screen_x;
	int	player_screen_y;
	int	map_width;
	int	map_height;

	get_map_dimensions(game, &map_width, &map_height);
	if (map_width > 0 && map_height > 0)
	{
		player_screen_x = (int)((game->player.pos_x / map_width) * 100) + 10;
		player_screen_y = (int)((game->player.pos_y / map_height) * 100) + 10;
		draw_player_dot(game, player_screen_x, player_screen_y);
	}
}

void	render_minimap(t_game *game)
{
	draw_map_grid(game);
	draw_player(game);
}
