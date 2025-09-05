/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:21:04 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 11:34:13 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_dir_config	get_dir_config(char direction)
{
	if (direction == 'N')
		return (get_north_config());
	else if (direction == 'S')
		return (get_south_config());
	else if (direction == 'E')
		return (get_east_config());
	else if (direction == 'W')
		return (get_west_config());
	else
		return (get_north_config());
}

static void	apply_direction_config(t_player *player, t_dir_config config)
{
	player->dir_x = config.dir_x;
	player->dir_y = config.dir_y;
	player->plane_x = config.plane_x;
	player->plane_y = config.plane_y;
}

void	set_direction_vectors(t_game *game, char direction)
{
	t_dir_config	config;

	config = get_dir_config(direction);
	apply_direction_config(&game->player, config);
}

int	init_player(t_game *game)
{
	game->player.pos_x = (double)game->map.player_x + 0.5;
	game->player.pos_y = (double)game->map.player_y + 0.5;
	set_direction_vectors(game, game->map.player_direction);
	return (1);
}
