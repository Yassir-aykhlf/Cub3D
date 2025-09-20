/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:39:45 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:39:46 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	handle_rotation(t_game *game)
{
	if (game->input.rot_left && game->input.rot_right)
	{
		if (game->input.last_rotation == DIR_LEFT)
			apply_rotation(&game->player, -ROT_SPEED);
		else if (game->input.last_rotation == DIR_RIGHT)
			apply_rotation(&game->player, ROT_SPEED);
	}
	else if (game->input.rot_left)
		apply_rotation(&game->player, -ROT_SPEED);
	else if (game->input.rot_right)
		apply_rotation(&game->player, ROT_SPEED);
}

void	handle_strafe_movement(t_game *game)
{
	if (game->input.move_left && game->input.move_right)
	{
		if (game->input.last_horizontal_move == DIR_LEFT)
		{
			apply_movement(game, -game->player.plane_x * MOVE_SPEED,
				-game->player.plane_y * MOVE_SPEED);
		}
		else if (game->input.last_horizontal_move == DIR_RIGHT)
		{
			apply_movement(game, game->player.plane_x * MOVE_SPEED,
				game->player.plane_y * MOVE_SPEED);
		}
	}
	else if (game->input.move_left)
	{
		apply_movement(game, -game->player.plane_x * MOVE_SPEED,
			-game->player.plane_y * MOVE_SPEED);
	}
	else if (game->input.move_right)
	{
		apply_movement(game, game->player.plane_x * MOVE_SPEED,
			game->player.plane_y * MOVE_SPEED);
	}
}
