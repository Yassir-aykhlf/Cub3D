/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:15:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 10:51:30 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	*get_color_field_ptr(t_game *game, t_color_type type)
{
	if (type == COLOR_FLOOR)
		return (&game->map.floor_color);
	else if (type == COLOR_CEILING)
		return (&game->map.ceiling_color);
	return (NULL);
}

int	parse_color_by_type(t_game *game, t_lexer_state *lexer, t_color_type type)
{
	int	*color_field;

	color_field = get_color_field_ptr(game, type);
	if (!color_field)
		return (CUBE_FAILURE);
	return (parse_color(game, lexer, color_field));
}

int	parse_floor_color(t_game *game, t_lexer_state *lexer)
{
	return (parse_color_by_type(game, lexer, COLOR_FLOOR));
}

int	parse_ceiling_color(t_game *game, t_lexer_state *lexer)
{
	return (parse_color_by_type(game, lexer, COLOR_CEILING));
}
