/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:38:03 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 11:34:13 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
	{
		printf("ESC pressed - exiting cleanly\n");
		game->running = 0;
		cleanup_game(game);
		exit(CUBE_SUCCESS);
	}
	else if (keycode == W_KEY)
		game->input.move_fwd = 1;
	else if (keycode == S_KEY)
		game->input.move_back = 1;
	else if (keycode == A_KEY)
		game->input.move_left = 1;
	else if (keycode == D_KEY)
		game->input.move_right = 1;
	else if (keycode == LEFT_ARROW)
		game->input.rot_left = 1;
	else if (keycode == RIGHT_ARROW)
		game->input.rot_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->input.move_fwd = 0;
	else if (keycode == S_KEY)
		game->input.move_back = 0;
	else if (keycode == A_KEY)
		game->input.move_left = 0;
	else if (keycode == D_KEY)
		game->input.move_right = 0;
	else if (keycode == LEFT_ARROW)
		game->input.rot_left = 0;
	else if (keycode == RIGHT_ARROW)
		game->input.rot_right = 0;
	return (0);
}

int	handle_close(t_game *game)
{
	printf("Window close button pressed - exiting cleanly\n");
	game->running = 0;
	cleanup_game(game);
	exit(CUBE_SUCCESS);
	return (0);
}

void	setup_event_hooks(t_game *game)
{
	mlx_hook(game->window.window, KEY_PRESS, 1L << 0,
		handle_keypress, game);
	mlx_hook(game->window.window, KEY_RELEASE, 1L << 1,
		handle_keyrelease, game);
	mlx_hook(game->window.window, DESTROY_NOTIFY, 1L << 17,
		handle_close, game);
	mlx_loop_hook(game->window.mlx_ptr, render_next_frame, game);
}
