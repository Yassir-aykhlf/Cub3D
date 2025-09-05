/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:25:10 by lazmoud           #+#    #+#             */
/*   Updated: 2025/08/21 10:27:14 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cube.h>

int	is_player(int c)
{
	return ((c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'));
}

int	find_player(char const *line)
{
	int	idx;
	int	target_index;
	int	found;

	idx = 0;
	found = 0;
	while (line[idx])
	{
		if (is_player(line[idx]))
		{
			target_index = idx;
			found++;
		}
		idx++;
	}
	if (found == 2)
		return (FOUND_MULTIPLE);
	if (found == 0)
		return (NOT_FOUND);
	return (target_index);
}

int	process_map_line(t_game *game, char *line)
{
	int		player;

	player = find_player(line);
	if (player == FOUND_MULTIPLE)
		return (log_duplication_error("player"));
	if (player != NOT_FOUND)
	{
		if (game->map.player_direction)
			return (log_duplication_error("player"));
		game->map.player_x = player;
		game->map.player_y = game->map.grid.size;
		game->map.player_direction = (line[player]);
		line[player] = '0';
	}
	push_line(&game->map.grid,
		line);
	return (CUBE_SUCCESS);
}

int	parse_map(t_game *game, t_lexer_state *lexer, t_token *store)
{
	char	*line;

	if (game->map.grid.size)
		return (log_duplication_error("map"));
	while (store->type == MAP_LINE)
	{
		line = store->u_data.string_data.items;
		if (process_map_line(game, line) != CUBE_SUCCESS)
			return (CUBE_FAILURE);
		init_token(store);
		if (!lexer_expect_token(lexer, MAP_LINE, store))
			break ;
	}
	if (!game->map.player_direction)
		return (log_missing("a player `N | S | W | E`"));
	return (CUBE_SUCCESS);
}
