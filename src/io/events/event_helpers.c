/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 17:40:42 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:40:43 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

void	handle_movement_keypress(int keycode, t_game *game)
{
	if (keycode == W_KEY || keycode == Z_KEY)
	{
		game->input.move_fwd = 1;
		game->input.last_vertical_move = DIR_FORWARD;
	}
	else if (keycode == S_KEY)
	{
		game->input.move_back = 1;
		game->input.last_vertical_move = DIR_BACKWARD;
	}
	else if (keycode == A_KEY || keycode == Q_KEY)
	{
		game->input.move_left = 1;
		game->input.last_horizontal_move = DIR_LEFT;
	}
	else if (keycode == D_KEY)
	{
		game->input.move_right = 1;
		game->input.last_horizontal_move = DIR_RIGHT;
	}
}

void	handle_rotation_keypress(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW)
	{
		game->input.rot_left = 1;
		game->input.last_rotation = DIR_LEFT;
	}
	else if (keycode == RIGHT_ARROW)
	{
		game->input.rot_right = 1;
		game->input.last_rotation = DIR_RIGHT;
	}
}

void	handle_movement_keyrelease(int keycode, t_game *game)
{
	if (keycode == W_KEY || keycode == Z_KEY)
	{
		game->input.move_fwd = 0;
		if (!game->input.move_back)
			game->input.last_vertical_move = DIR_NONE;
	}
	else if (keycode == S_KEY)
	{
		game->input.move_back = 0;
		if (!game->input.move_fwd)
			game->input.last_vertical_move = DIR_NONE;
	}
	else if (keycode == A_KEY || keycode == Q_KEY)
	{
		game->input.move_left = 0;
		if (!game->input.move_right)
			game->input.last_horizontal_move = DIR_NONE;
	}
	else if (keycode == D_KEY)
	{
		game->input.move_right = 0;
		if (!game->input.move_left)
			game->input.last_horizontal_move = DIR_NONE;
	}
}

void	handle_rotation_keyrelease(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW)
	{
		game->input.rot_left = 0;
		if (!game->input.rot_right)
			game->input.last_rotation = DIR_NONE;
	}
	else if (keycode == RIGHT_ARROW)
	{
		game->input.rot_right = 0;
		if (!game->input.rot_left)
			game->input.last_rotation = DIR_NONE;
	}
}
