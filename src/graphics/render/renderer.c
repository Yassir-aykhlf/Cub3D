/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 09:37:51 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/20 17:40:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

long	get_time_diff_us(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * MSEC
		+ (end->tv_usec - start->tv_usec));
}

static void	limit_frame_rate(t_game *game)
{
	struct timeval	current_time;
	long			elapsed_us;
	long			sleep_time;

	gettimeofday(&current_time, NULL);
	elapsed_us = get_time_diff_us(&game->last_frame_time, &current_time);
	if (elapsed_us < MSEC_PER_FRAME)
	{
		sleep_time = MSEC_PER_FRAME - elapsed_us;
		usleep(sleep_time);
		gettimeofday(&current_time, NULL);
	}
	game->last_frame_time = current_time;
}

int	render_next_frame(t_game *game)
{
	if (!game->running)
		return (0);
	update_player_state(game);
	limit_frame_rate(game);
	cast_all_rays(game);
	mlx_put_image_to_window(game->window.mlx_ptr,
		game->window.window, game->screen_buffer.img_ptr, 0, 0);
	return (0);
}
