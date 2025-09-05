/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:40:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static void	safe_free_string(char **str_ptr)
{
	if (*str_ptr)
	{
		free(*str_ptr);
		*str_ptr = NULL;
	}
}

void	cleanup_map(t_map *map)
{
	safe_free_string(&map->north_texture);
	safe_free_string(&map->south_texture);
	safe_free_string(&map->west_texture);
	safe_free_string(&map->east_texture);
	destroy_lines(&map->grid);
}

void	cleanup_game(t_game *game)
{
	cleanup_images(game);
	cleanup_textures(game);
	cleanup_map(&game->map);
	cleanup_window(&game->window);
	game->running = 0;
}
