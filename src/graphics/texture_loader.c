/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:40:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 12:48:09 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	load_texture_image(t_game *game, int tex_type, char *path)
{
	game->textures[tex_type].img_ptr = mlx_xpm_file_to_image(
			game->window.mlx_ptr, path,
			&game->textures[tex_type].width,
			&game->textures[tex_type].height);
	if (game->textures[tex_type].img_ptr == NULL)
		log_system_error(path);
	return (game->textures[tex_type].img_ptr != NULL);
}

static void	get_texture_data_addresses(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->textures[i].addr = mlx_get_data_addr(
				game->textures[i].img_ptr,
				&game->textures[i].bpp,
				&game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		game->textures[i].img_ptr = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
	if (!load_texture_image(game, TEXTURE_NORTH, game->map.north_texture))
		return (0);
	if (!load_texture_image(game, TEXTURE_SOUTH, game->map.south_texture))
		return (0);
	if (!load_texture_image(game, TEXTURE_WEST, game->map.west_texture))
		return (0);
	if (!load_texture_image(game, TEXTURE_EAST, game->map.east_texture))
		return (0);
	get_texture_data_addresses(game);
	return (1);
}
