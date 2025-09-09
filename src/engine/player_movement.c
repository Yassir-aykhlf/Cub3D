/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:35:20 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 11:35:21 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	apply_rotation(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

static int	is_wall(t_game *game, int x, int y)
{
	if (y < 0 || y >= (int)game->map.grid.size)
		return (1);
	if (x < 0 || x >= (int)strlen(game->map.grid.items[y]))
		return (1);
	return (game->map.grid.items[y][x] == '1');
}

static void	apply_movement(t_game *game, double move_x, double move_y)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x + move_x;
	next_y = game->player.pos_y + move_y;
	if (!is_wall(game, (int)next_x, (int)game->player.pos_y))
		game->player.pos_x = next_x;
	if (!is_wall(game, (int)game->player.pos_x, (int)next_y))
		game->player.pos_y = next_y;
}

static void	handle_forward_backward(t_game *game)
{
	if (game->input.move_fwd)
		apply_movement(game, game->player.dir_x * MOVE_SPEED,
			game->player.dir_y * MOVE_SPEED);
	if (game->input.move_back)
		apply_movement(game, -game->player.dir_x * MOVE_SPEED,
			-game->player.dir_y * MOVE_SPEED);
}

void	update_player_state(t_game *game)
{
	if (game->input.rot_left)
		apply_rotation(&game->player, -ROT_SPEED);
	if (game->input.rot_right)
		apply_rotation(&game->player, ROT_SPEED);
	handle_forward_backward(game);
	if (game->input.move_left)
		apply_movement(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	if (game->input.move_right)
		apply_movement(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
}
