/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:48:10 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 11:02:30 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static int	validate_texture_field(char *texture, const char *texture_name)
{
	if (!texture)
		return (log_missing(texture_name));
	return (CUBE_SUCCESS);
}

static int	validate_required_textures(t_map *map)
{
	if (validate_texture_field(map->north_texture, "a north texture")
		!= CUBE_SUCCESS)
		return (CUBE_FAILURE);
	if (validate_texture_field(map->south_texture, "a south texture")
		!= CUBE_SUCCESS)
		return (CUBE_FAILURE);
	if (validate_texture_field(map->west_texture, "a west texture")
		!= CUBE_SUCCESS)
		return (CUBE_FAILURE);
	if (validate_texture_field(map->east_texture, "an east texture")
		!= CUBE_SUCCESS)
		return (CUBE_FAILURE);
	return (CUBE_SUCCESS);
}

int	validate_map(t_map *map)
{
	if (!map->grid.size)
		return (log_missing("a game map"));
	if (validate_required_textures(map) != CUBE_SUCCESS)
		return (CUBE_FAILURE);
	if (map->ceiling_color == -1)
		return (log_missing("The ceiling color"));
	if (map->floor_color == -1)
		return (log_missing("The floor color"));
	if (validate_map_walls(map) == CUBE_FAILURE)
		return (CUBE_FAILURE);
	return (CUBE_SUCCESS);
}

int	flood_fill_validate(t_map *map, int **visited, int x, int y)
{
	char			current_char;
	t_coord			pos;

	if (!is_within_bounds(map, x, y))
		return (CUBE_SUCCESS);
	current_char = get_char_at(map, x, y);
	if (is_visited(visited, x, y)
		|| current_char == ' ')
		return (CUBE_SUCCESS);
	mark_visited(visited, x, y);
	if (is_at_boundary(map, x, y) && current_char != '1')
		return (CUBE_FAILURE);
	pos.x = x;
	pos.y = y;
	return (process_flood_fill_directions(map, visited, pos));
}
