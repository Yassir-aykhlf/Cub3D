/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:30:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/08/21 15:01:41 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	print_grid(char **items, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("%s\n", items[i]);
		i++;
	}
}

static void	print_north_south_textures(t_game *game)
{
	const char	*north_str;
	const char	*south_str;

	if (game->map.north_texture)
		north_str = game->map.north_texture;
	else
		north_str = "NULL";
	if (game->map.south_texture)
		south_str = game->map.south_texture;
	else
		south_str = "NULL";
	printf("North texture: %s\n", north_str);
	printf("South texture: %s\n", south_str);
}

static void	print_west_east_textures(t_game *game)
{
	const char	*west_str;
	const char	*east_str;

	if (game->map.west_texture)
		west_str = game->map.west_texture;
	else
		west_str = "NULL";
	if (game->map.east_texture)
		east_str = game->map.east_texture;
	else
		east_str = "NULL";
	printf("West texture: %s\n", west_str);
	printf("East texture: %s\n", east_str);
}

static void	print_colors(t_game *game)
{
	printf("Floor color: %d (0x%06X)\n", game->map.floor_color,
		game->map.floor_color);
	printf("Ceiling color: %d (0x%06X)\n", game->map.ceiling_color,
		game->map.ceiling_color);
}

void	print_parsed_config(t_game *game)
{
	printf("=== PARSED CONFIGURATION ===\n");
	print_north_south_textures(game);
	print_west_east_textures(game);
	print_colors(game);
	print_grid(game->map.grid.items, game->map.grid.size);
}
