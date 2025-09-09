/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 11:07:52 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_direction(t_map *map, int **visited, t_coord pos, t_coord dir)
{
	return (flood_fill_validate(map, visited, pos.x + dir.x, pos.y + dir.y));
}

int	process_flood_fill_directions(t_map *map, int **visited, t_coord pos)
{
	const int		directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	t_coord			dir;
	int				i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		dir.x = directions[i][0];
		dir.y = directions[i][1];
		if (check_direction(map, visited, pos, dir) == CUBE_FAILURE)
			return (CUBE_FAILURE);
		i++;
	}
	return (CUBE_SUCCESS);
}

int	validate_map_walls(t_map *map)
{
	int		**visited;
	int		result;
	t_coord	player_pos;

	visited = allocate_visited_matrix(map);
	if (!visited)
		return (CUBE_FAILURE);
	player_pos.x = map->player_x;
	player_pos.y = map->player_y;
	result = flood_fill_validate(map, visited, player_pos.x, player_pos.y);
	free_visited_matrix(visited, map->grid.size);
	if (result == CUBE_FAILURE)
		return (log_map_not_enclosed());
	return (CUBE_SUCCESS);
}
