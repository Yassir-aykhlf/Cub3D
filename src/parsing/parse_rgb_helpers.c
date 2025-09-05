/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	parse_color(t_game *game, t_lexer_state *lexer, int *color_field)
{
	int	color;

	(void)game;
	color = parse_rgb_color(lexer);
	if (color != CUBE_FAILURE)
	{
		*color_field = color;
		return (CUBE_SUCCESS);
	}
	return (color);
}

int	parse_texture(t_game *game, t_lexer_state *lexer, char **texture_field)
{
	char	*path;

	(void)game;
	path = get_texture_path(lexer);
	if (path == NULL)
		return (CUBE_FAILURE);
	if (*texture_field)
		free(*texture_field);
	*texture_field = path;
	return (CUBE_SUCCESS);
}
