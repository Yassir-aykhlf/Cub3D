/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:25:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*get_texture_path(t_lexer_state *lexer)
{
	t_token	token;
	char	*path;

	if (get_and_validate_token(lexer, WORD, &token) == CUBE_FAILURE)
		return (NULL);
	skip_whitespace(lexer);
	path = ft_strdup(token.u_data.string_data.items, NULL);
	cleanup_token(&token);
	return (path);
}

static char	**get_texture_field_ptr(t_game *game, t_texture_type type)
{
	if (type == TEXTURE_NORTH)
		return (&game->map.north_texture);
	else if (type == TEXTURE_SOUTH)
		return (&game->map.south_texture);
	else if (type == TEXTURE_WEST)
		return (&game->map.west_texture);
	else if (type == TEXTURE_EAST)
		return (&game->map.east_texture);
	return (NULL);
}

int	parse_texture_by_type(t_game *game, t_lexer_state *lexer,
		t_texture_type type)
{
	char	**texture_field;

	texture_field = get_texture_field_ptr(game, type);
	if (!texture_field)
		return (CUBE_FAILURE);
	return (parse_texture(game, lexer, texture_field));
}
