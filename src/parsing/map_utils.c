/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/08/21 15:01:41 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

/**
 * Check if position is within map bounds
 */
int	is_within_bounds(t_map *map, int x, int y)
{
	if (y < 0 || y >= (int)map->grid.size)
		return (0);
	if (x < 0)
		return (0);
	if (x >= (int)strlen(map->grid.items[y]))
		return (0);
	return (1);
}

/**
 * Check if character is walkable (floor or player)
 */
int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Get character at position (handle out of bounds)
 */
char	get_char_at(t_map *map, int x, int y)
{
	if (!is_within_bounds(map, x, y))
		return (' ');
	return (map->grid.items[y][x]);
}

/**
 * Check if position is at map boundary or next to space
 */
int	is_at_boundary(t_map *map, int x, int y)
{
	if (y == 0 || y == (int)map->grid.size - 1)
		return (1);
	if (x == 0)
		return (1);
	if (x >= (int)strlen(map->grid.items[y]) - 1)
		return (1);
	if (get_char_at(map, x + 1, y) == ' ')
		return (1);
	if (get_char_at(map, x - 1, y) == ' ')
		return (1);
	if (get_char_at(map, x, y + 1) == ' ')
		return (1);
	if (get_char_at(map, x, y - 1) == ' ')
		return (1);
	return (0);
}

/**
 * Allocate 2D visited matrix
 */
int	**allocate_visited_matrix(t_map *map)
{
	int	**visited;
	int	i;

	visited = malloc(sizeof(int *) * map->grid.size);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < (int)map->grid.size)
	{
		visited[i] = malloc(sizeof(int) * strlen(map->grid.items[i]));
		if (!visited[i])
		{
			free_visited_matrix(visited, i);
			return (NULL);
		}
		memset(visited[i], 0, sizeof(int) * strlen(map->grid.items[i]));
		i++;
	}
	return (visited);
}
