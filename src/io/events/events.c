/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:38:03 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:40:53 by yaykhlf          ###   ########.fr       */
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
	handle_movement_keypress(keycode, game);
	handle_rotation_keypress(keycode, game);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	handle_movement_keyrelease(keycode, game);
	handle_rotation_keyrelease(keycode, game);
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
