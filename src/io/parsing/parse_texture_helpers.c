/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaykhlf <yaykhlf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:00 by yaykhlf           #+#    #+#             */
/*   Updated: 2025/09/05 15:44:35 by yaykhlf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	parse_north_texture(t_game *game, t_lexer_state *lexer)
{
	return (parse_texture_by_type(game, lexer, TEXTURE_NORTH));
}

int	parse_south_texture(t_game *game, t_lexer_state *lexer)
{
	return (parse_texture_by_type(game, lexer, TEXTURE_SOUTH));
}

int	parse_west_texture(t_game *game, t_lexer_state *lexer)
{
	return (parse_texture_by_type(game, lexer, TEXTURE_WEST));
}

int	parse_east_texture(t_game *game, t_lexer_state *lexer)
{
	return (parse_texture_by_type(game, lexer, TEXTURE_EAST));
}
