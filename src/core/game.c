/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:09:34 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/09 11:13:11 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static int	parse_and_validate_config(t_game *game);

int	init_game(t_game *game)
{
	if (!parse_and_validate_config(game))
		return (0);
	if (!init_window(&game->window, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d"))
		return (0);
	if (!init_screen_buffer(game))
		return (0);
	memset(game->textures, 0, sizeof(game->textures));
	if (!init_textures(game))
		return (0);
	if (!init_player(game))
		return (0);
	memset(&game->input, 0, sizeof(t_input));
	game->running = 1;
	gettimeofday(&game->last_frame_time, NULL);
	return (1);
}

static int	parse_and_validate_config(t_game *game)
{
	t_lines			lines;
	int				code;
	t_lexer_state	lexer;

	memset(&lexer, 0, sizeof(lexer));
	memset(&lines, 0, sizeof(lines));
	lexer.lines = &lines;
	if (!read_file_into_lines(lexer.lines, game->map.config_file_path))
	{
		perror("cub3d");
		return (0);
	}
	code = parse_game_config(game, &lexer);
	destroy_lines(lexer.lines);
	if (code != CUBE_SUCCESS || validate_map(&game->map) == CUBE_FAILURE)
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}

int	init_screen_buffer(t_game *game)
{
	game->screen_buffer.img_ptr = mlx_new_image(game->window.mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->screen_buffer.img_ptr)
	{
		perror("Failed to create screen buffer");
		return (0);
	}
	game->screen_buffer.addr = mlx_get_data_addr(game->screen_buffer.img_ptr,
			&game->screen_buffer.bpp,
			&game->screen_buffer.line_len,
			&game->screen_buffer.endian);
	return (1);
}

int	run_game(t_game *game)
{
	setup_event_hooks(game);
	printf("Window created successfully. Press ESC or close window to exit.\n");
	mlx_loop(game->window.mlx_ptr);
	return (0);
}
