/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>

static void	safe_destroy_mlx_image(void *mlx_ptr, void **img_ptr)
{
	if (*img_ptr)
	{
		mlx_destroy_image(mlx_ptr, *img_ptr);
		*img_ptr = NULL;
	}
}

void	cleanup_images(t_game *game)
{
	safe_destroy_mlx_image(game->window.mlx_ptr,
		(void **)&game->screen_buffer.img_ptr);
}

void	cleanup_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		safe_destroy_mlx_image(game->window.mlx_ptr,
			(void **)&game->textures[i].img_ptr);
		i++;
	}
}
